#pragma once
#include "CommonPlayer.h"
class Arm : public CommonPlayer
{
public:
	Arm(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void Draw(NetPlayer *otherplayer, Player *player) override;
};