#include <iostream>
#include <cstdlib> // для system
#include "const.h"
#include "world.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
#include <glfw3.h>
#include "functions.h"
#include "player.h"
#include "physics.h"

	Player::Player(World *world)
	{
		currslot = 0;
		position = world->startpos;
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		world->currchank = world->defChunk(position.x, position.z);
		jumpingSpeed = 0;
		for (int i = 0; i < 24; i++)
		{
			slots[i].id = 0;
			slots[i].num = 0;
		}
		for (int i = 0; i < 1024; i++)
		{
			keys[i] = false;
		}
		jumping = false;
		for (int i = 0; i < 5; i++)
		{
			craftSlots[i].id = 0;
			craftSlots[i].num = 0;
		}
		for (int i = 0; i < 10; i++)
		{
			benchCraftSlots[i].id = 0;
			benchCraftSlots[i].num = 0;
		}
		buf.id = 0;
		buf.num = 0;
		currslot = 0;
		settingBlock = 1;
		health = 100.0f;
	}

	void Player::doMovement(World *world, bool isOpenedInterface, SocketTCP *socket)
	{
		int oldchunk = world->currchank;
		GLfloat cameraSpeed = 5.0f * world->deltaTime;
		GLfloat acceleration = -(0.01);
		oldPos = position;
		right = glm::normalize(glm::cross(front, up));
		forward = glm::normalize(glm::cross(right, up));

		if (keys[GLFW_KEY_LEFT_SHIFT])
		{
			cameraSpeed*=2;
		}
		if (keys[GLFW_KEY_LEFT_CONTROL])
		{
			cameraSpeed /= 2;
		}
		if (!isOpenedInterface)
		{
			if (keys[GLFW_KEY_W])
			{
				position -= cameraSpeed * forward;
			}
			if (keys[GLFW_KEY_S])
			{
				position += cameraSpeed * forward;
			}
			if (keys[GLFW_KEY_A])
			{
				position -= right * cameraSpeed;
			}
			if (keys[GLFW_KEY_D])
			{
				position += right * cameraSpeed;
			}

		}
		if (jumping)
		{
			position += jumpingSpeed * up;
			jumpingSpeed += acceleration;
		}
		if (keys[GLFW_KEY_SPACE] && !jumping)
		{
			jumping = true;
			jumpingSpeed = 0.15f;
		}
		physics::moveFormTo(oldPos, world, this);
		if (!jumping && !world->exInChunck(myfloor(position.x), myfloor(position.y - 2.0f), myfloor(position.z), world->currchank))
		{
			jumping = true;
			jumpingSpeed = 0.0f;
		}
		if (oldchunk != world->currchank)
		{
			socket->sendReqToNewChunk(world->currchank);
			world->LoadChunksAround(world->currchank);
		}
		/*if (oldPos!=position)
			std::cout << position.x << " " << position.z << " " << World->currchank << std::endl;*/
	}

void Player::processControls()
{
	glfwPollEvents();
}

bool Player::isChangedPos()
{
	return oldPos != position;
}

void Player::addToInventory(int num, int id)
{
	for (int i = 0; i < 24; i++)
	{
		if (slots[i].id == id && slots[i].num + num <= 64)
		{
			slots[i].num += num;
			return;
		}
	}
	for (int i = 0; i < 24; i++)
	{
		if (slots[i].id == 0)
		{
			slots[i].id = id;
			slots[i].num = num;
			return;
		}
	}
}

int Player::decFromInventory(int num, int numslot)
{
	int ret = slots[numslot].id;
	if (ret < STARTINSTRUMENTS)
		slots[numslot].num-=num;
	if (slots[numslot].num <= 0)
	{
		slots[numslot].id = 0;
		slots[numslot].num = 0;
	}
	return ret;
}