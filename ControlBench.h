#pragma once
#include "Player.h"
static class ControlBench
{
public:
	static void processLeftMouse(Player *player, float x, float y);
	static void processRightMouse(Player *player, float x, float y);
private:
	static int defSlot(float x, float y, bool* isCraft);
};

