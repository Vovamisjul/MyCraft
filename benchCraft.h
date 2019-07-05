#pragma once
#include "player.h"



static class benchCraft {
public:
	static void craft(Player *player);

	static bool tryCraftPlanks(Player *player);
	static bool tryCraftSticks(Player *player);
	static bool tryCraftBench(Player *player);
	static bool tryCraftStoneBricks(Player *player);
	static bool tryCraftFurnace(Player *player);
	static bool tryCraftWoodenPickaxe(Player *player);

};