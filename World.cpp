#pragma once
#include <iostream>
#include <cstdlib> // дл€ system
#include "const.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "world.h"
#include "Furnace.h"


World::World(int seed)
	{
		std::srand(seed);
		for (int i = 0; i < 64; i++)
			nodes[i] = std::rand() & 3;

		for (int i = 0; i < allChunks*allChunks; i++)
			loadedChunks[i] = false;
		currchank = defChunk(startpos.x, startpos.z);

		LoadChunksAround(currchank);
	}

	void World::LoadChunksAround(int numChunk)
	{
 		for (int loadChunkY = numChunk - 4 * allChunks; loadChunkY < numChunk + 5 * allChunks; loadChunkY += allChunks)
		{
			for (int loadChunkX = -4; loadChunkX < 5; loadChunkX++)
			{
				if (!loadedChunks[loadChunkY + loadChunkX])
				{
					LoadChunk(loadChunkY + loadChunkX);
					loadedChunks[loadChunkY + loadChunkX] = true;
				}
			}
		}
		renderBlocks();
	}

	void World::LoadChunk(int numChunk)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				float h = noise(numChunk, j, k);
				float biome = noiseBioms(numChunk, j, k);
				int height = h * 7 + 55;
				//int biome = 5;
				//int height = 30;
				/*if (k == 5 && numChunk == 82 && j == 9)
				std::cout << "s" << std::endl;*/
				int istree = std::rand() & 127;
				int isCactus = std::rand() & 255;
				for (int i = 0; i < 64; i++)
				{
					cubePositions[i * 16 * 16 + j * 16 + k] = glm::vec3((float)k, (float)i, (float)j);
					if (biome > -0.2)
					{
						int isOre = std::rand() & 127;
						int isClay = std::rand() & 511;
						int isMelon = std::rand() & 1023;
						if (biome < -0.1)
							height = h * (4 - (biome + 0.1) * 30) + 55 + (biome + 0.1) * 100;
						if (istree == 0 && i <= height + 3 && i >= height)
						{
							if (i + 1 == height + 3)
							{
								int treeheight = std::rand() & 1;
								if (treeheight)
									forEachNearBlock(k, i + 1, j, numChunk, blocktype::LEAVE, false);
								forEachNearBlock(k, i + 2, j, numChunk, blocktype::LEAVE, false);
							}
							blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::LOG;
							numblocksInLayer[i][numChunk]++;
						}
						if (isMelon == 0 && i == height)
							blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::MELON;
						if (i < height)
						{
							if (i == height - 1)
								blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::GRASS;
							else
								if (i >= height - 5)
								{
									if (isClay == 0)
									{
										forEachNearBlock(k, i, j, numChunk, blocktype::CLAY, true);
									}
									else
										blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::DIRT;
								}
								else
								{
									if (isOre == 0)
									{
										int ore = std::rand() & 31;
										if (ore < 6)
										{
											forEachNearBlock(k, i, j, numChunk, blocktype::IRONORE, true);
										}
										else if (ore < 14)
										{
											forEachNearBlock(k, i, j, numChunk, blocktype::COPPERORE, true);
										}
										else if (ore < 24)
										{
											forEachNearBlock(k, i, j, numChunk, blocktype::COALORE, true);
										}
										else if (ore < 28 && height < 30)
										{
											forEachNearBlock(k, i, j, numChunk, blocktype::GOLDORE, true);
										}
										else if (ore < 30 && height < 20)
										{
											forEachNearBlock(k, i, j, numChunk, blocktype::EMERALDORE, true);
										}
										else if (height < 10)
										{
											forEachNearBlock(k, i, j, numChunk, blocktype::DIAMONDORE, true);
										}
									}
									else
										blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::STONE;
								}
							numblocksInLayer[i][numChunk]++;
						}
					}
					else
					{
						height = h * 4 + 45;
						if (i< height + 3 && isCactus == 0)
							blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::CACTUS;
						if (i < height)
						{
							if (i >= height - 5)
								blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::SAND;
							else
								blockType[i * 16 * 16 + j * 16 + k][numChunk] = blocktype::STONE;
							numblocksInLayer[i][numChunk]++;
						}
					}
					blockType[0 + j * 16 + k][numChunk] = blocktype::ENDSTONE;
				}

			}
		}
	}

	void World::forEachNearBlock(int x, int y, int z, int chunk, int blockType, bool AddSpot)
	{
		setBlock(x, y, z, chunk, blockType);
		setBlock(x, y, z - 1, chunk, blockType);
		setBlock(x, y, z + 1, chunk, blockType);
		setBlock(x - 1, y, z, chunk, blockType);
		setBlock(x - 1, y, z - 1, chunk, blockType);
		setBlock(x - 1, y, z + 1, chunk, blockType);
		setBlock(x + 1, y, z, chunk, blockType);
		setBlock(x + 1, y, z - 1, chunk, blockType);
		setBlock(x + 1, y, z + 1, chunk, blockType);
		y--;
		setBlock(x, y, z, chunk, blockType);
		setBlock(x, y, z - 1, chunk, blockType);
		setBlock(x, y, z + 1, chunk, blockType);
		setBlock(x - 1, y, z, chunk, blockType);
		setBlock(x - 1, y, z - 1, chunk, blockType);
		setBlock(x - 1, y, z + 1, chunk, blockType);
		setBlock(x + 1, y, z, chunk, blockType);
		setBlock(x + 1, y, z - 1, chunk, blockType);
		setBlock(x + 1, y, z + 1, chunk, blockType);
		if (!AddSpot)
			return;
		int addSpot = std::rand() & 15;
		if (addSpot < 4)
		{
			setBlock(x, y + 1, z, chunk, blockType);
			setBlock(x, y + 1, z - 1, chunk, blockType);
			setBlock(x - 1, y + 1, z, chunk, blockType);
			setBlock(x - 1, y + 1, z - 1, chunk, blockType);
		}
		else if (addSpot < 8)
		{
			setBlock(x + 2, y, z, chunk, blockType);
			setBlock(x + 2, y, z - 1, chunk, blockType);
			setBlock(x + 2, y + 1, z, chunk, blockType);
			setBlock(x + 2, y + 1, z - 1, chunk, blockType);
		}
		else if (addSpot < 12)
		{
			setBlock(x - 2, y , z, chunk, blockType);
			setBlock(x - 2, y, z - 1, chunk, blockType);
			setBlock(x - 2, y + 1, z, chunk, blockType);
			setBlock(x - 2, y + 1, z - 1, chunk, blockType);
		}
		else
		{
			setBlock(x, y + 1, z - 2, chunk, blockType);
			setBlock(x, y - 1, z - 2, chunk, blockType);
			setBlock(x - 1, y + 1, z - 2, chunk, blockType);
			setBlock(x - 1, y + 1, z - 2, chunk, blockType);
		}

	}

	void World::setBlock(int x, int y, int z, int chunk, int blockType)
	{
		if (y < 0)
			return;
		if (x < 0)
		{
			x += 16;
			chunk -= allChunks;
		}
		if (x > 15)
		{
			x -= 16;
			chunk += allChunks;
		}
		if (z < 0)
		{
			z += 16;
			chunk--;
		}
		if (z > 15)
		{
			z -= 16;
			chunk++;
		}
		this->blockType[y * 16 * 16 + z * 16 + x][chunk] = blockType;
	}

	void World::setBlock(int x, int y, int z, int blockType)
	{
		int chunk = defChunk(x, y);
		this->blockType[y * 16 * 16 + (z % 16) * 16 + x % 16][chunk] = blockType;
	}

	bool World::exInChunck(float x, float y, float z, int numChunk)
	{
		//if (y >= 50 || z >= 16 || x >= 16 || y <0 || z <0 || x <0) return false;
		if (blockType[int(y) * 16 * 16 + (int(z) % 16) * 16 + int(x) % 16][numChunk]) return true;			//cubePositions[i * 16 * 16 + j * 16 + k] = glm::vec3((float)k, (float)i, (float)j);
		return false;
	}

	void World::renderBlocks()
	{
		for (int ch1 = -2; ch1<3; ch1++)
			for (int ch2 = currchank - 2; ch2 < currchank + 3; ch2++)
			{
				int ch = ch2 - ch1*allChunks;
				int localchunk = ch2 + 2 - currchank + (ch1 + 2) * drawedChunks;
				for (GLuint i1 = 0; i1 < 64; i1++)
				{
					if (makeLayer(i1, ch))
						for (GLuint i2 = 0; i2 < 16 * 16; i2++)
						{
							if (drawBlock(cubePositions[i1 * 16 * 16 + i2], ch))
							{
								toDraw[i1 * 16 * 16 + i2][localchunk] = blockType[i1 * 16 * 16 + i2][ch];
							}
							else
								toDraw[i1 * 16 * 16 + i2][localchunk] = 0;
						}
					else
					{
						for (GLuint i2 = 0; i2 < 16 * 16; i2++)
							toDraw[i1 * 16 * 16 + i2][localchunk] = 0;
					}
				}
			}
	}

	bool World::makeLayer(int numlayer, int numChunk)
	{
		if (numlayer == 0 || numlayer == 63)
			return true;
		int a = numChunk % allChunks;
		if (numChunk < allChunks || numChunk >= allChunks*(allChunks - 1) || a == 0 || a == allChunks - 1)
			return true;
		return !(numblocksInLayer[numlayer][numChunk] == 16 * 16) || !(numblocksInLayer[numlayer - 1][numChunk] == 16 * 16) || !(numblocksInLayer[numlayer + 1][numChunk] == 16 * 16) ||
			!(numblocksInLayer[numlayer][numChunk - 1] == 16 * 16) || !(numblocksInLayer[numlayer][numChunk + 1] == 16 * 16) || !(numblocksInLayer[numlayer][numChunk - allChunks] == 16 * 16) || !(numblocksInLayer[numlayer + 1][numChunk + allChunks] == 16 * 16);
	}

	int World::defChunk(float x, float z)
	{
		int xcoord = (int)floorf(x + 0.5f) / 16;
		int zcoord = (int)floorf(z + 0.5f) / 16;
		return xcoord*allChunks + zcoord;
	}

	int World::defChunk(int x, int z, int chunk)
	{
		x = (x + (chunk / allChunks) * 16) / 16;
		z = (z + (chunk % allChunks) * 16) / 16;
		return x*allChunks + z;
	}


	bool World::drawBlock(glm::vec3 block, int numChunk)
	{
		if (block.y >= 63 || block.y <= 0) return false;
		for (int j = 0; j < 6; j++)
		{
			glm::vec3 nearBlock = block + nearPositions[j];
			if (nearBlock.z >= 0 && nearBlock.x >= 0 && nearBlock.z < 16 && nearBlock.x < 16)
			{
				if (isTransparent(int(nearBlock.y * 16 * 16 + nearBlock.z * 16 + nearBlock.x),numChunk)) return true;
			}
			else
			{
				if (isTransparent(int(nearBlock.y * 16 * 16 + ((int(nearBlock.z) + 16) % 16) * 16 + (int(nearBlock.x) + 16) % 16), defChunk((int)nearBlock.x, (int)nearBlock.z, numChunk))) return true;
			}
		}
		return false;
	}

	bool World::isTransparent(int localpos, int chunk)
	{
		if (blockType[localpos][chunk] == blocktype::AIR || blockType[localpos][chunk] == blocktype::LEAVE || blockType[localpos][chunk] == blocktype::GLASS)
			return true;
		return false;
	}

	/*int world::numBlocks(int numlayer, int numChunk)
	{
		if (numlayer == -1) return 0;
		int res = 0;
		for (int i = 0; i < 16 * 16; i++)
			if (blockType[numlayer * 16 * 16 + i][numChunk]) res++;
		return res;
	}*/

	float* World::pseudoRand(int x, int y)
	{
		float res[2];
		int a = ((x * 3643) ^ (y * 4217) + 3643 + 4217) & 63;
		a = nodes[a];
		if (a == 0)
		{
			res[0] = 1;
			res[1] = 0;
		}
		if (a == 1)
		{
			res[0] = -1;
			res[1] = 0;
		}
		if (a == 2)
		{
			res[0] = 0;
			res[1] = 1;
		}
		if (a == 3)
		{
			res[0] = 0;
			res[1] = -1;
		}
		return res;
	}

	float World::QunticCurve(float t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	float World::Dot(float* a, float* b)
	{
		return a[0] * b[0] + a[1] * b[1];
	}

	float World::lerp(float a, float b, float t)
	{
		return a + (b - a) * t;
	}

	float World::noise(int ch, int i, int j)
	{
		int left = (ch % allChunks);
		int top = (ch / allChunks);
		float pointInQuadX = i / 16.0;
		float pointInQuadY = j / 16.0;
		float topLeftGradient[2] = { pseudoRand(left, top)[0], pseudoRand(left, top)[1] };
		float topRightGradient[2] = { pseudoRand(left + 1, top)[0], pseudoRand(left + 1, top)[1] };
		float bottomLeftGradient[2] = { pseudoRand(left, top + 1)[0], pseudoRand(left, top + 1)[1] };
		float bottomRightGradient[2] = { pseudoRand(left + 1, top + 1)[0], pseudoRand(left + 1, top + 1)[1] };

		float distanceToTopLeft[2] = { pointInQuadX, pointInQuadY };
		float distanceToTopRight[2] = { pointInQuadX - 1, pointInQuadY };
		float distanceToBottomLeft[2] = { pointInQuadX, pointInQuadY - 1 };
		float distanceToBottomRight[2] = { pointInQuadX - 1, pointInQuadY - 1 };

		pointInQuadX = QunticCurve(pointInQuadX);
		pointInQuadY = QunticCurve(pointInQuadY);

		// собственно, интерпол€ци€:
		float tx1 = Dot(distanceToTopLeft, topLeftGradient);
		float tx2 = Dot(distanceToTopRight, topRightGradient);
		float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
		float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

		pointInQuadX = QunticCurve(pointInQuadX);
		pointInQuadY = QunticCurve(pointInQuadY);

		float tx = lerp(tx1, tx2, pointInQuadX);
		float bx = lerp(bx1, bx2, pointInQuadX);
		float tb = lerp(tx, bx, pointInQuadY);

		return tb;
	}

	float World::noiseBioms(int ch, int i, int j)
	{
		int left = (ch % allChunks);
		int top = (ch / allChunks);
		i = left * 16 + i;
		j = top * 16 + j;
		left = (i / 128);
		top = (j / 128);
		float pointInQuadX = (i % 128) / 128.0;
		float pointInQuadY = (j % 128) / 128.0;
		float topLeftGradient[2] = { pseudoRand(left, top)[0], pseudoRand(left, top)[1] };
		float topRightGradient[2] = { pseudoRand(left + 1, top)[0], pseudoRand(left + 1, top)[1] };
		float bottomLeftGradient[2] = { pseudoRand(left, top + 1)[0], pseudoRand(left, top + 1)[1] };
		float bottomRightGradient[2] = { pseudoRand(left + 1, top + 1)[0], pseudoRand(left + 1, top + 1)[1] };

		float distanceToTopLeft[2] = { pointInQuadX, pointInQuadY };
		float distanceToTopRight[2] = { pointInQuadX - 1, pointInQuadY };
		float distanceToBottomLeft[2] = { pointInQuadX, pointInQuadY - 1 };
		float distanceToBottomRight[2] = { pointInQuadX - 1, pointInQuadY - 1 };


		// собственно, интерпол€ци€:
		float tx1 = Dot(distanceToTopLeft, topLeftGradient);
		float tx2 = Dot(distanceToTopRight, topRightGradient);
		float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
		float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

		pointInQuadX = QunticCurve(pointInQuadX);
		pointInQuadY = QunticCurve(pointInQuadY);

		float tx = lerp(tx1, tx2, pointInQuadX);
		float bx = lerp(bx1, bx2, pointInQuadX);
		float tb = lerp(tx, bx, pointInQuadY);

		return tb;
	}

Furnace * World::findFurnace(glm::vec3 coords)
{
	for (int i = 0; i < furnaceVec.size(); i++)
	{
		if (furnaceVec[i]->pos == coords)
			return furnaceVec[i];
	}
	return NULL;
}

void World::deleteFromVec(Furnace *furnace)
{
	for (int i = 0; i < furnaceVec.size(); i++)
	{
		if (furnaceVec[i] == furnace)
		{
			furnaceVec.erase(furnaceVec.begin() + i);
			return;
		}
	}
}