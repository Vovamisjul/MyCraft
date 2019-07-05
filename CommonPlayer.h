#pragma once
#include "Model.h"
#include "Shader.h"
#include "Player.h"
#include "NetPlayer.h"

class CommonPlayer : public Model, public Shader
{
public:
	CommonPlayer(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual void Draw(NetPlayer *otherplayer, Player *player) = 0;
};