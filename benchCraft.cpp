#include "benchCraft.h"
#include "const.h"
#include <vector>

typedef bool(*craftRecipes)(Player *player);

void benchCraft::craft(Player *player)
{
	std::vector<craftRecipes> CraftRecipes = { tryCraftPlanks , tryCraftSticks, tryCraftBench, tryCraftStoneBricks, tryCraftFurnace, tryCraftWoodenPickaxe };
	for each (craftRecipes craftRecipe in CraftRecipes)
	{
		if ((*craftRecipe)(player))
			return;
	}
}

bool benchCraft::tryCraftPlanks(Player *player)
{
	bool res;
	int validCrafts[9][9] = {
		blocktype::LOG, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::LOG, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::LOG, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::LOG, blocktype::AIR, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::LOG, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::LOG, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::LOG,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR,blocktype::LOG, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::LOG };
	for (int i = 0; i < 9; i++)
	{
		res = true;
		for (int j = 0; j < 9; j++)
		{
			res = res && player->benchCraftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->benchCraftSlots[9].id = blocktype::PLANK;
		player->benchCraftSlots[9].num = 4;
	}
	else
	{
		player->benchCraftSlots[9].id = blocktype::AIR;
		player->benchCraftSlots[9].num = 0;
	}
	return res;
}

bool benchCraft::tryCraftSticks(Player *player)
{
	return false;
}

bool benchCraft::tryCraftBench(Player *player)
{
	bool res;
	int validCrafts[4][9] = {
		blocktype::PLANK, blocktype::PLANK, blocktype::AIR, blocktype::PLANK, blocktype::PLANK, blocktype::AIR, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::PLANK, blocktype::PLANK, blocktype::AIR, blocktype::PLANK, blocktype::PLANK, blocktype::AIR,blocktype::AIR, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::PLANK, blocktype::PLANK, blocktype::AIR, blocktype::PLANK,blocktype::PLANK, blocktype::AIR,
		blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::AIR, blocktype::PLANK, blocktype::PLANK, blocktype::AIR,blocktype::PLANK, blocktype::PLANK};
	for (int i = 0; i < 4; i++)
	{
		res = true;
		for (int j = 0; j < 9; j++)
		{
			res = res && player->benchCraftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->benchCraftSlots[9].id = blocktype::WBENCH;
		player->benchCraftSlots[9].num = 1;
	}
	else
	{
		player->benchCraftSlots[9].id = blocktype::AIR;
		player->benchCraftSlots[9].num = 0;
	}
	return res;

}

bool benchCraft::tryCraftStoneBricks(Player *player)
{
	bool res;
	int validCrafts[4][9] = {
		blocktype::STONE, blocktype::STONE, blocktype::AIR, 
		blocktype::STONE, blocktype::STONE, blocktype::AIR, 
		blocktype::AIR,blocktype::AIR, blocktype::AIR,

		blocktype::AIR, blocktype::STONE, blocktype::STONE, 
		blocktype::AIR, blocktype::STONE, blocktype::STONE, 
		blocktype::AIR,blocktype::AIR, blocktype::AIR,

		blocktype::AIR, blocktype::AIR, blocktype::AIR,
		blocktype::STONE, blocktype::STONE, blocktype::AIR,
		blocktype::STONE,blocktype::STONE, blocktype::AIR,

		blocktype::AIR, blocktype::AIR, blocktype::AIR, 
		blocktype::AIR, blocktype::STONE, blocktype::STONE, 
		blocktype::AIR,blocktype::STONE, blocktype::STONE };
	for (int i = 0; i < 4; i++)
	{
		res = true;
		for (int j = 0; j < 9; j++)
		{
			res = res && player->benchCraftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->benchCraftSlots[9].id = blocktype::STONEBRICKS;
		player->benchCraftSlots[9].num = 4;
	}
	else
	{
		player->benchCraftSlots[9].id = blocktype::AIR;
		player->benchCraftSlots[9].num = 0;
	}
	return res;

}

bool benchCraft::tryCraftFurnace(Player *player)
{
	bool res;
	int validCrafts[1][9] = {
		blocktype::STONE, blocktype::STONE, blocktype::STONE, 
		blocktype::STONE, blocktype::AIR, blocktype::STONE, 
		blocktype::STONE, blocktype::STONE, blocktype::STONE };
	for (int i = 0; i < 1; i++)
	{
		res = true;
		for (int j = 0; j < 9; j++)
		{
			res = res && player->benchCraftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->benchCraftSlots[9].id = blocktype::FURNACE;
		player->benchCraftSlots[9].num = 1;
	}
	else
	{
		player->benchCraftSlots[9].id = blocktype::AIR;
		player->benchCraftSlots[9].num = 0;
	}
	return res;

}

bool benchCraft::tryCraftWoodenPickaxe(Player *player)
{
	bool res;
	int validCrafts[2][9] = {
		blocktype::PLANK, blocktype::PLANK, blocktype::PLANK,
		blocktype::PLANK, blocktype::STONE, blocktype::AIR,
		blocktype::PLANK, blocktype::AIR, blocktype::STONE,

		blocktype::PLANK, blocktype::PLANK, blocktype::PLANK,
		blocktype::AIR, blocktype::STONE, blocktype::PLANK,
		blocktype::STONE, blocktype::AIR, blocktype::PLANK };
	for (int i = 0; i < 2; i++)
	{
		res = true;
		for (int j = 0; j < 9; j++)
		{
			res = res && player->benchCraftSlots[j].id == validCrafts[i][j];
		}
		if (res)
			break;
	}
	if (res)
	{
		player->benchCraftSlots[9].id = instrumentType::WOODENPICKAXE;
		player->benchCraftSlots[9].num = 1;
	}
	else
	{
		player->benchCraftSlots[9].id = blocktype::AIR;
		player->benchCraftSlots[9].num = 0;
	}
	return res;
}