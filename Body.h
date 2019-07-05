#pragma once
#include "CommonPlayer.h"

class Body : public CommonPlayer
{
public:
	Body(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void Draw(NetPlayer *otherplayer, Player *player) override;
};