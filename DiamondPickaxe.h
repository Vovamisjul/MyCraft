#pragma once
#include "CommonModel.h"
#include "Player.h"
class DiamondPickaxe : public CommonModel
{
public:
	DiamondPickaxe(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(Player *player, World *World) override;
	void drawInNetPlayer(Player *player, NetPlayer *netPlayer, World *World) override;
};