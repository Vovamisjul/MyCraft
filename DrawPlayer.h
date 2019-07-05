#pragma once
#include "Head.h"
#include "Body.h"
#include "Leg.h"
#include "Arm.h"

class DrawPlayer {
public:
	void Draw(NetPlayer *otherplayer, Player *player);
private:
	Head *head = new Head("textures/3d/steve/head/head.fbx", "shaders/3dvertex.txt", "shaders/3dfragment.txt");
	Body *body = new Body("textures/3d/steve/body/body.fbx", "shaders/3dvertex.txt", "shaders/3dfragment.txt");
	Leg *leg = new Leg("textures/3d/steve/leg/leg.fbx", "shaders/3dvertex.txt", "shaders/3dfragment.txt");
	Arm *arm = new Arm("textures/3d/steve/arm/arm.fbx", "shaders/3dvertex.txt", "shaders/3dfragment.txt");
};