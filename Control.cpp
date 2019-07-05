#include "control.h"
#include "player.h"
#include "functions.h"
#include "inventory.h"
#include "Furnace.h"
#include "playersCraft.h"
#include "benchCraft.h"
#include <glfw3.h>
#include <glm/glm.hpp>
#include "ControlBench.h"
#include "Controlinv.h"
#include "ControlFurnace.h"
#include "ControlWorld.h"

Control::Control(Player *player, World *world)
{
	breakedBlock = 0;
	breakedChunk = 0;
	breakingTime = 0;
	breakeBlock = false;
	player->settingBlock = 0;
	this->player = player;
	this->world = world;
	showInv = false;
	blocksBreakedByInstrument[0] = NULL;
	blocksBreakedByInstrument[1] = blocksBreakedByWoodenAxe;
	blocksBreakedByInstrument[2] = blocksBreakedByWoodenPickaxe;
}

void Control::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (showBench)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			showBench = false;
		} else
		if (showFurnace)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			showFurnace = false;
		} else
		if (showInv)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			showInv = false;
		} else
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
		player->keys[key] = true;
	else if (action == GLFW_RELEASE)
		player->keys[key] = false;
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (showBench)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			showBench = false;
			return;
		}
		if (showFurnace)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			showFurnace = false;
			return;
		}
		showInv = !showInv;
		if (showInv)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
		{
			if (player->buf.id != 0)
			{
				player->slots[player->bufslot] = player->buf;
				player->buf.id = 0;
				player->buf.num = 0;
			}
			for (int i = 0; i < 4; i++)
			{
				if (player->craftSlots[i].id)
				{
					player->addToInventory(player->craftSlots[i].num, player->craftSlots[i].id);
					player->craftSlots[i].id = 0;
					player->craftSlots[i].num = 0;
				}
			}
			player->craftSlots[4].id = 0;
			player->craftSlots[4].num = 0;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}

void Control::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // эта переменная была проинициализирована значением true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз 
	lastX = xpos;
	lastY = ypos;

	if (!showInv && !showBench && !showFurnace)
	{
		GLfloat sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		player->front = glm::normalize(front);
		if (xoffset != 0 && yoffset != 0)
		{
			if (clickedLeft)
			{
				startBreaking();
			}
		}
	}
}

void Control::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (!showInv && !showBench && !showFurnace)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			clickedLeft = true;
			startBreaking();
			tryHitPlayer();
			//std::cout << int(myfloor(posx)) << int(myfloor(posy)) << int(myfloor(posz)) << std::endl;
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			clickedLeft = false;
			breakeBlock = false;
			//std::cout << int(myfloor(posx)) << int(myfloor(posy)) << int(myfloor(posz)) << std::endl;
		}
		int radius = 0;
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			float posx = player->position.x, posy = player->position.y, posz = player->position.z;
			while (radius < 40)
			{
				posx = posx + player->front.x / 10;
				posy = posy + player->front.y / 10;
				posz = posz + player->front.z / 10;
				if (world->exInChunck(myfloor(posx), myfloor(posy), myfloor(posz), world->defChunk(posx, posz)) && radius < 40)
				{
					if (world->blockType[int(myfloor(posy)) * 16 * 16 + (int(myfloor(posz)) % 16) * 16 + int(myfloor(posx)) % 16][world->defChunk(posx, posz)] == blocktype::WBENCH)
					{
						glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
						showBench = true;
						return;
					}
					if (world->blockType[int(myfloor(posy)) * 16 * 16 + (int(myfloor(posz)) % 16) * 16 + int(myfloor(posx)) % 16][world->defChunk(posx, posz)] == blocktype::FURNACE)
					{
						glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
						showFurnace = true;
						clickedCoords = glm::vec3(myfloor(posx), myfloor(posy), myfloor(posz));
						clickedFurnace = world->findFurnace(clickedCoords);
						return;
					}
					posx = posx - player->front.x / 10;
					posy = posy - player->front.y / 10;
					posz = posz - player->front.z / 10;
					break;
				}

				radius++;
			}
			if (radius != 40 && !locationAllPlayersInBlock(myfloor(posx), (posy), myfloor(posz)) && !showBench)
			{
				int id = player->decFromInventory(1, player->currslot);
				if (id != 0)
				{
					if (id < NUMBLOCKS)
					{
						int settedBlock = int(myfloor(posy)) * 16 * 16 + (int(myfloor(posz)) % 16) * 16 + int(myfloor(posx)) % 16;
						int settedChunk = world->defChunk(posx, posz);
						socket->sendCoords(settedBlock, settedChunk, id, true);
						world->blockType[int(myfloor(posy)) * 16 * 16 + (int(myfloor(posz)) % 16) * 16 + int(myfloor(posx)) % 16][world->defChunk(posx, posz)] = id;
						world->numblocksInLayer[int(myfloor(posy))][world->defChunk(myfloor(posx), myfloor(posz))]--;
					}
					if (id == blocktype::FURNACE)
						world->furnaceVec.push_back(new Furnace(glm::vec3(myfloor(posx), myfloor(posy), myfloor(posz))));
					world->renderBlocks();
				}
				player->settingBlock = 0;
			}
		}
	}
	else if (showInv)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			ControlInv::processLeftMouse(player, lastX / width, lastY / height);
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			ControlInv::processRightMouse(player, lastX / width, lastY / height);

		playersCraft::craft(player);
	}
	else if (showBench)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			ControlBench::processLeftMouse(player, lastX / width, lastY / height);
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			ControlBench::processRightMouse(player, lastX / width, lastY / height);

		benchCraft::craft(player);
	}
	else if (showFurnace)
	{

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			ControlFurnace::processLeftMouse(player, clickedFurnace, lastX / width, lastY / height);
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			ControlFurnace::processRightMouse(player, clickedFurnace, lastX / width, lastY / height);

		clickedFurnace->startMelt();
	}
}


void Control::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	player->currslot -= yoffset;
	if (player->currslot < 0)
		player->currslot += 24;
	if (player->currslot > 23)
		player->currslot -= 24;
}

bool Control::locationAllPlayersInBlock(float x, float y, float z)
{
	if (player->position.x > x - 0.51f && player->position.x < x + 0.51f &&
		player->position.y > y - 0.01f && player->position.y < y + 2.01f &&
		player->position.z > z - 0.51f && player->position.z < z + 0.51f)
		return true;
	return ((locationOtherPlayerInBlock(x, y, z)) != -1);
}

int Control::locationOtherPlayerInBlock(float x, float y, float z)
{
	for (int i = 0; i < world->PlayersVec.size(); i++)
	{
		if (world->PlayersVec[i]->position.x - playerWidth < x && world->PlayersVec[i]->position.x + playerWidth > x &&
			world->PlayersVec[i]->position.y - 1.5f < y && world->PlayersVec[i]->position.y + 0.5f > y  &&
			world->PlayersVec[i]->position.z - playerWidth < z && world->PlayersVec[i]->position.z + playerWidth > z)
			return world->PlayersVec[i]->id;
	}
	return -1;
}

void Control::startBreaking()
{
	int breakedBlockOld = breakedBlock;
	int breakedChunkOld = breakedChunk;
	if (breakeBlock)
	{
		if (ControlWorld::processLeftMouse(player, world, &this->breakingBlock))
		{
			breakedBlock = int(myfloor(breakingBlock.y)) * 16 * 16 + (int(myfloor(breakingBlock.z)) % 16) * 16 + int(myfloor(breakingBlock.x)) % 16;
			breakedChunk = world->defChunk(breakingBlock.x, breakingBlock.z);
			if (breakedBlock != breakedBlockOld || breakedChunk != breakedChunkOld)
			{
				breakingTime = 0;
				player->settingBlock = 0;
			}
		}
	}
	else
	{
		if (ControlWorld::processLeftMouse(player, world, &this->breakingBlock))
		{
			breakeBlock = true;
			breakedBlock = int(myfloor(breakingBlock.y)) * 16 * 16 + (int(myfloor(breakingBlock.z)) % 16) * 16 + int(myfloor(breakingBlock.x)) % 16;
			breakedChunk = world->defChunk(breakingBlock.x, breakingBlock.z);
			breakingTime = 0;
			player->settingBlock = 0;
		}

	}
}

void Control::processBreaking()
{
	if (breakeBlock)
	{
		tryAddTime();
		if (breakingTime >= breakingTimes[world->blockType[breakedBlock][breakedChunk]])
		{
			breakingTime = 0;
			player->settingBlock = 0;
			breakeBlock = false;
			player->addToInventory(1, world->blockType[breakedBlock][breakedChunk]);
			socket->sendCoords(breakedBlock, breakedChunk, 0, false);
			if (world->blockType[breakedBlock][breakedChunk] == blocktype::FURNACE)
			{
				Furnace *furnace = world->findFurnace(breakingBlock);
				world->deleteFromVec(furnace);
				delete furnace;
			}
			world->blockType[breakedBlock][breakedChunk] = 0;
			world->numblocksInLayer[int(myfloor(breakingBlock.y))][breakedChunk]--;
			world->renderBlocks();
			startBreaking();
		}
		else
		{
			if (player->settingBlock >= 0.2f)
				player->settingBlock = 0;
		}
	}
}

void Control::tryAddTime()
{
	if (player->slots[player->currslot].id >= STARTINSTRUMENTS)
	{
		int numinstrument = player->slots[player->currslot].id - STARTINSTRUMENTS;
		for (int i = 0; i < numBreakable[numinstrument]; i++)
		{
			if (*(blocksBreakedByInstrument[numinstrument]+i) == world->blockType[breakedBlock][breakedChunk])
				breakingTime += (world->deltaTime)*multiplyerByInstrument[numinstrument];
		}
	}
}

int Control::getTextureBroken()
{
	return int(breakingTime / breakingTimes[world->blockType[breakedBlock][breakedChunk]] * 8);
}

void Control::tryHitPlayer()
{
	int radius = 0;
	float posx = player->position.x, posy = player->position.y, posz = player->position.z;
	int id = -1;
	while (radius < 40 && id == -1)
	{
		id = locationOtherPlayerInBlock(posx, posy, posz);
		posx = posx + player->front.x / 10;
		posy = posy + player->front.y / 10;
		posz = posz + player->front.z / 10;
		radius++;
	}
	if (radius != 40 && id != -1)
	{
		int damage = 1;
		if (player->slots[player->currslot].id >= STARTINSTRUMENTS)
			damage = damageByInstruments[player->slots[player->currslot].id - STARTINSTRUMENTS];
		socket->sendHit(id, damage);
		player->settingBlock = 0;
	}
}