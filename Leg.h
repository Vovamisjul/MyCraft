#pragma once
#include "CommonPlayer.h"
class Leg : public CommonPlayer
{
public:
	Leg(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void Draw(NetPlayer *otherplayer, Player *player) override;
};