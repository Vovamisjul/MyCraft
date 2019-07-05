#include "ControlWorld.h"
#include "functions.h"

bool ControlWorld::processLeftMouse(Player *player, World *world, glm::vec3 *position)
{
	int radius = 0;
	float posx = player->position.x, posy = player->position.y, posz = player->position.z;
	while (!world->exInChunck(myfloor(posx), myfloor(posy), myfloor(posz), world->defChunk(posx, posz)) && radius < 40)
	{
		posx = posx + player->front.x / 10;
		posy = posy + player->front.y / 10;
		posz = posz + player->front.z / 10;
		radius++;
	}
	*position = glm::vec3(posx, posy, posz);
	return radius < 40;
}