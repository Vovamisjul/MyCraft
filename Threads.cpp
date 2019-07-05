#define GLM_ENABLE_EXPERIMENTAL
#include "Threads.h"
#include "glfw3.h"
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

std::thread Threads::threadTCP;
std::thread Threads::threadUDP;

void Threads::StartRecieve(World *world, Player *player, SOCKET sockTCP, SOCKET sockUDP, bool *endRecieve)
{
	threadTCP = std::thread(RecieveCoordsTCP, world, player, sockTCP, endRecieve);
	threadUDP = std::thread(RecieveCoordsUDP, world, sockUDP, endRecieve);
}

void Threads::RecieveCoordsTCP(World *world, Player *player, SOCKET sock, bool *endRecieve)
{
	int block;
	int chunk;
	int type;
	int action;
	char mess[5000];
	int damage;
	do
	{
		int res = recv(sock, mess, 5000, 0);
		if (res != -1)
		{
			int i;
			float timeHit;
			switch (mess[0])
			{
			case DAMAGE:
				DefineDamage(mess, &damage);
				timeHit = glfwGetTime();
				if (timeHit - player->timeLastHit > 1)
				{
					player->health -= damage;
					player->timeLastHit = timeHit;
				}
				break;
			case FIRSTCOORDS:
				i = 1;
				while (i < res)
				{
					DefineCoords(mess + i, &block, &chunk, &type);
					if (mess[i] == SENDEDCOORDSSET)
					{
						world->numblocksInLayer[block / (16 * 16)][chunk]++;
						world->blockType[block][chunk] = type;
						if (type == blocktype::FURNACE)
							world->furnaceVec.push_back(new Furnace(glm::vec3(block % 16 + (chunk / allChunks) * 16, block / (16 * 16), (block % (16 * 16)) / 16 + (chunk % allChunks) * 16)));
					}
					if (mess[i] == SENDEDCOORDSGET)
					{
						world->numblocksInLayer[block / (16 * 16)][chunk]--;
						if (world->blockType[block][chunk] == blocktype::FURNACE)
						{
							Furnace *furnace = world->findFurnace(glm::vec3(block % 16 + (chunk / allChunks) * 16, block / (16 * 16), (block % (16 * 16)) / 16 + (chunk % allChunks) * 16));
							world->deleteFromVec(furnace);
							delete furnace;
						}
						world->blockType[block][chunk] = 0;
					}
					i += 1 + 3 * sizeof(int);
				}
				world->renderBlocks();
				break;
			case ANOTHERBLOCK:
				DefineCoords(mess + 1, &block, &chunk, &type);
				if (mess[1] == SENDEDCOORDSSET)
				{
					world->numblocksInLayer[block / (16 * 16)][chunk]++;
					world->blockType[block][chunk] = type;
					if (type == blocktype::FURNACE)
						world->furnaceVec.push_back(new Furnace(glm::vec3(block % 16 + (chunk / allChunks) * 16, block / (16 * 16), (block % (16 * 16)) / 16 + (chunk % allChunks) * 16)));
				}
				if (mess[1] == SENDEDCOORDSGET)
				{
					world->numblocksInLayer[block / (16 * 16)][chunk]--;
					if (world->blockType[block][chunk] == blocktype::FURNACE)
					{
						Furnace *furnace = world->findFurnace(glm::vec3(block % 16 + (chunk / allChunks) * 16, block / (16 * 16), (block % (16 * 16)) / 16 + (chunk % allChunks) * 16));
						world->deleteFromVec(furnace);
						delete furnace;
					}
					world->blockType[block][chunk] = 0;
				}
				world->renderBlocks();
				break;
			default:
				break;
			}
		}
	} while (!*endRecieve);
}

void Threads::RecieveCoordsUDP(World *world, SOCKET sock, bool *endRecieve)
{
	char buf[2 + 2 * sizeof(glm::vec3) + sizeof(bool) + sizeof(char)];
	NetPlayer *player = new NetPlayer();
	struct sockaddr_in ssa;
	int size = sizeof(ssa);
	int res = -1;
	while (!*endRecieve)
	{
		if (res > 0)
		{
			player->id = buf[1];
			switch (buf[0])
			{
			case COORDS:
			{
				player->position = *((glm::vec3 *)(buf + 2));
				player->looking = *((glm::vec3 *)(buf + 2 + sizeof(glm::vec3)));
				player->lookingbody = player->looking;
				bool hitting = *((bool *)(buf + 2 + 2 * sizeof(glm::vec3)));
				char blockType = *((char *)(buf + 2 + 2 * sizeof(glm::vec3) + sizeof(bool)));
				bool find = false;
				auto iter = world->PlayersVec.begin();

				while (iter != world->PlayersVec.end())
				{
					if ((*iter)->id == player->id)
					{
						if ((*iter)->position != player->position)
						{
							if (!(*iter)->going)
							{
								(*iter)->going = true;
								if ((*iter)->movingLeg > 2 * PI)
									(*iter)->movingLeg = 0;
							}
							(*iter)->lookingbody = (*iter)->looking = player->looking;
							(*iter)->position = player->position;
						}
						else
						{
							(*iter)->going = false;
						}
						if (!(*iter)->hitting && hitting)
						{
							(*iter)->timeHitting = 0.0f;
						}
						(*iter)->hitting = hitting;
						float diffangle = glm::orientedAngle(player->looking, (*iter)->looking, glm::vec3(0.0f, 1.0f, 0.0f));
						(*iter)->looking = player->looking;
						//(*iter)->blockType = blockType;
						float diffheadbody = glm::orientedAngle((*iter)->lookingbody, (*iter)->looking, glm::vec3(0.0f, 1.0f, 0.0f));
						if (fabs(diffheadbody) > PI / 5)
						{
							(*iter)->lookingbody = glm::rotate((*iter)->lookingbody, -diffangle, glm::vec3(0.0f, 1.0f, 0.0f));
						}
						find = true;
						break;
					}
					++iter;
				}
				if (!find)
				{
					world->PlayersVec.push_back(new NetPlayer(player->position, player->looking, player->id));
				}
				break;
			}
			case DISCONNECT:
			{
				for (int i = 0; i < world->PlayersVec.size(); i++)
				{
					if (world->PlayersVec[i]->id == player->id)
					{
						delete world->PlayersVec[i];
						world->PlayersVec.erase(world->PlayersVec.cbegin() + i);
						break;
					}
				}
				break;
			}
			}
		}
		res = recvfrom(sock, buf, 2 + 2 * sizeof(glm::vec3) + sizeof(bool) + sizeof(char), 0, (struct sockaddr *)&ssa, &size);
	}
}

void Threads::FinishRecieve()
{
	threadTCP.detach();
	threadUDP.detach();
}

void Threads::DefineCoords(char *mess, int *block, int *chunk, int *type)
{
	*block = *((int *)(mess + 1));
	*chunk = *((int *)(mess + 1 + sizeof(int)));
	*type = *((int *)(mess + 1 + 2 * sizeof(int)));
}

void Threads::DefineDamage(char *mess, int *damage)
{
	*damage = *((int *)(mess + 1));
}