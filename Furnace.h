#pragma once
#include "const.h"
#include <glm/glm.hpp>
#define sizeofmelted 7
#define sizeofburning 4

class Furnace {
public:
	slot slots[3]; //0 - melt; 1 - burn; 2 - result
	bool melting = false;
	glm::vec3 pos;
	Furnace(glm::vec3 pos);
	void startMelt();
	void cancelMelt();
	void processMelt(float dT);
	float givePrcBurn();
	float givePrcMelt();
private:
	int burningInd = -1;
	int meltingInd = -1;
	float timeofmelting;
	float timeofburning;
	const float meltingTime = 8;
	const int melted[sizeofmelted] =  { blocktype::CLAY,	   blocktype::COPPERORE,      blocktype::DIAMONDORE, blocktype::GOLDORE,	  blocktype::IRONORE,      blocktype::LOG,     blocktype::SAND};
	const int results[sizeofmelted] = { blocktype::BACKEDCLAY, notBlocktype::COPPERINGOT, notBlocktype::DIAMOND, notBlocktype::GOLDINGOT, notBlocktype::IRONINGOT, notBlocktype::COAL, blocktype::GLASS };
	const int burning[sizeofburning] = { blocktype::LEAVE, blocktype::LOG, blocktype::PLANK, blocktype::WBENCH};
	const float burningtime[sizeofburning] = { 4.05f, 24.05f, 8.05f, 16.05f };
	void giveResult();
};