#pragma once
#include "CommonPlayer.h"
class Head : public CommonPlayer 
{
public:
	Head(string path, const GLchar* vertexPath, const GLchar* fragmentPath);
	void Draw(NetPlayer *otherplayer, Player *player) override;
};