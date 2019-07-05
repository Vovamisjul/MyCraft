#pragma once
#include <iostream>
#include <cstdlib> // для system
#include "const.h"
#include "glew.h"
#include "Furnace.h"
#include "NetPlayer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class World
{
public:
	glm::vec3 cubePositions[16 * 16 * 64];
	int blockType[16 * 16 * 64][allChunks*allChunks];
	bool loadedChunks[allChunks*allChunks];
	int toDraw[16 * 16 * 64][drawedChunks*drawedChunks];
	glm::vec3 startpos = glm::vec3(600.0f, 50.0f, 300.0f);
	int currchank;
	float deltaTime;
	std::vector<Furnace *> furnaceVec;
	std::vector<NetPlayer *> PlayersVec;

	World(int seed);

	void LoadChunksAround(int numChunk);

	void LoadChunk(int numChunk);

	bool exInChunck(float x, float y, float z, int numChunk);

	void renderBlocks();

	bool makeLayer(int numlayer, int numChunk);

	int defChunk(float x, float z);

	bool drawBlock(glm::vec3 block, int numChunk);

	int numblocksInLayer[64][allChunks*allChunks];

	Furnace *findFurnace(glm::vec3 coords);
	void deleteFromVec(Furnace *furnace);
	void setBlock(int x, int y, int z, int blockType);
private:

	int nodes[64];

	glm::vec3 nearPositions[6]
	{
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f) }; 

	int defChunk(int x, int z, int chunk);

	void forEachNearBlock(int x, int y, int z, int chunk, int blockType, bool AddSpot);

	bool isTransparent(int localpos, int chunk);

	void setBlock(int x, int y, int z, int chunk, int blockType);

	float* pseudoRand(int x, int y);

	float QunticCurve(float t);

	float Dot(float* a, float* b);

	float lerp(float a, float b, float t);

	float noise(int ch, int i, int j);

	float noiseBioms(int ch, int i, int j);
};