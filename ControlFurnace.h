#pragma once
#include "Player.h"
#include "Furnace.h"

static class ControlFurnace
{
public:
	static void processLeftMouse(Player *player, Furnace *furnace, float x, float y);
	static void processRightMouse(Player *player, Furnace *furnace, float x, float y);
private:
	static int defSlot(float x, float y, bool* furnace);
};