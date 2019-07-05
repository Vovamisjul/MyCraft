#pragma once
#include "player.h"

static class playersCraft {
public:
	static void craft(Player *player);

	static bool tryCraftPlanks(Player *player);
	static bool tryCraftSticks(Player *player);
	static bool tryCraftBench(Player *player);
	
};