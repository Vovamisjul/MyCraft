#include "playersCraft.h"
#include "const.h"
#include <vector>

typedef bool (* craftRecipes)(Player *player);

void playersCraft::craft(Player *player)
{
	std::vector<craftRecipes> CraftRecipes = { tryCraftPlanks , tryCraftSticks, tryCraftBench};
	for each (craftRecipes craftRecipe in CraftRecipes)
	{
		if ((*craftRecipe)(player))
			return;
	}
}

bool playersCraft::tryCraftPlanks(Player *player)
{
	bool res;
	int validCrafts[4][4] = { 
		blocktype::LOG, blocktype::AIR, blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::LOG, blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::LOG, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::LOG };
	for (int i = 0; i < 4; i++)
	{
		res = true;
		for (int j = 0; j < 4; j++)
		{
			res = res && player->craftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->craftSlots[4].id = blocktype::PLANK;
		player->craftSlots[4].num = 4;
	}
	else
	{
		player->craftSlots[4].id = blocktype::AIR;
		player->craftSlots[4].num = 0;
	}
	return res;
}

bool playersCraft::tryCraftSticks(Player *player)
{
	return false;
}

bool playersCraft::tryCraftBench(Player *player)
{
	bool res;
	int validCrafts[1][4] = {
		blocktype::PLANK, blocktype::PLANK, blocktype::PLANK, blocktype::PLANK };
	for (int i = 0; i < 1; i++)
	{
		res = true;
		for (int j = 0; j < 4; j++)
		{
			res = res && player->craftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->craftSlots[4].id = blocktype::WBENCH;
		player->craftSlots[4].num = 1;
	}
	else
	{
		player->craftSlots[4].id = blocktype::AIR;
		player->craftSlots[4].num = 0;
	}
	return res;

}