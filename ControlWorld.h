#pragma once
#include "Player.h"
static class ControlWorld
{
public:
	static bool processLeftMouse(Player *player, World *world, glm::vec3 *position);
	static void processRightMouse(Player *player);
};