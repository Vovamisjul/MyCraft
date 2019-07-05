#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "world.h"
#include "physics.h"
#include "player.h"
#include "functions.h"

float const physics::width = 0.2f;

void physics::moveFormTo(glm::vec3 oldPos, World *world, Player *player)
{
	float diffx = player->position.x - oldPos.x;
	float diffy = player->position.y - oldPos.y;
	float diffz = player->position.z - oldPos.z;
	glm::vec3 localPos;
	localPos = oldPos;
	localPos.x += diffx;
	/*if (diffx != 0)
	printf_s("f");*/
	if (intersect(localPos, world))
	{

		localPos.x -= diffx;
	}
	localPos.y += diffy;
	if (intersect(localPos, world))
	{
		player->jumping = false;
		int damage = -player->jumpingSpeed * 20;
		if (damage > 6)
		{
			player->health -= damage;
		}
		localPos.y -= diffy;
		localPos.y = floorf(localPos.y);
	}
	localPos.z += diffz;
	if (intersect(localPos, world))
	{
		localPos.z -= diffz;
	}
	player->position = localPos;
	world->currchank = world->defChunk(localPos.x, localPos.z);
}

bool physics::intersect(glm::vec3 localPos, World *world)
{
	int localChunk0 = world->defChunk(localPos.x - width, localPos.z - width);
	int localChunk1 = world->defChunk(localPos.x + width, localPos.z + width);
	int localChunk2 = world->defChunk(localPos.x + width, localPos.z - width);
	int localChunk3 = world->defChunk(localPos.x - width, localPos.z + width);
	return world->exInChunck(myfloor(localPos.x - width), myfloor(localPos.y - 1.5f), myfloor(localPos.z - width), localChunk0) ||
		world->exInChunck(myfloor(localPos.x + width), myfloor(localPos.y - 1.5f), myfloor(localPos.z + width), localChunk1) ||
		world->exInChunck(myfloor(localPos.x + width), myfloor(localPos.y - 1.5f), myfloor(localPos.z - width), localChunk2) ||
		world->exInChunck(myfloor(localPos.x - width), myfloor(localPos.y - 1.5f), myfloor(localPos.z + width), localChunk3) ||

		world->exInChunck(myfloor(localPos.x - width), myfloor(localPos.y - 0.5f), myfloor(localPos.z - width), localChunk0) ||
		world->exInChunck(myfloor(localPos.x + width), myfloor(localPos.y - 0.5f), myfloor(localPos.z + width), localChunk1) ||
		world->exInChunck(myfloor(localPos.x + width), myfloor(localPos.y - 0.5f), myfloor(localPos.z - width), localChunk2) ||
		world->exInChunck(myfloor(localPos.x - width), myfloor(localPos.y - 0.5f), myfloor(localPos.z + width), localChunk3) ||

		world->exInChunck(myfloor(localPos.x - width), myfloor(localPos.y + 0.2f), myfloor(localPos.z - width), localChunk0) ||
		world->exInChunck(myfloor(localPos.x + width), myfloor(localPos.y + 0.2f), myfloor(localPos.z + width), localChunk1) ||
		world->exInChunck(myfloor(localPos.x + width), myfloor(localPos.y + 0.2f), myfloor(localPos.z - width), localChunk2) ||
		world->exInChunck(myfloor(localPos.x - width), myfloor(localPos.y + 0.2f), myfloor(localPos.z + width), localChunk3) ||
		intersectPlayers(localPos, world);
}

bool physics::intersectPlayers(glm::vec3 localPos, World *world)
{
	for each (NetPlayer *netPlayer in world->PlayersVec)
	{
		if (netPlayer->position.x + width > localPos.x - width && netPlayer->position.x - width < localPos.x + width &&
			netPlayer->position.z + width > localPos.z - width && netPlayer->position.z - width < localPos.z + width &&
			netPlayer->position.y + 0.5f > localPos.y - 1.5f && netPlayer->position.y - 1.5f < localPos.y + 0.5f)
			return true;
	}
	return false;
}