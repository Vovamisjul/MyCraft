#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "world.h"
#include "player.h"
static class physics {

public: 

	static void moveFormTo(glm::vec3 oldPos, World *world, Player *player);

private:

	static bool intersect(glm::vec3 localPos, World *world);
	static bool intersectPlayers(glm::vec3 localPos, World *world);
	static float const width;

};