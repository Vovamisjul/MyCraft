#pragma once
#include "CommonModel.h"
#include "Player.h"
class DiamondAxe : public CommonModel
{
public:
	DiamondAxe(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(Player *player, World *World) override;
	void drawInNetPlayer(Player *player, NetPlayer *netPlayer, World *World) override;
};