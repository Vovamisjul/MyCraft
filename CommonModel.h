#pragma once
#include "Model.h"
#include "Shader.h"
#include "Player.h"

class CommonModel : public Model, public Shader
{
public:
	CommonModel(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual void draw(Player *player, World *World) = 0;
	virtual void drawInNetPlayer(Player *player, NetPlayer *netPlayer, World *World) = 0;
};