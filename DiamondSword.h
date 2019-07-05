#pragma once
#include "CommonModel.h"
#include "Player.h"
#include "NetPlayer.h"
class DiamondSword : public CommonModel
{
public:
	DiamondSword(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(Player *player, World *World) override;
	void drawInNetPlayer(Player *player, NetPlayer *netPlayer, World *World) override;

};