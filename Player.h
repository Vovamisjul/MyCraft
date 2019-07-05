#pragma once
#include <glm/glm.hpp>
#include "World.h"
#include "SocketTCP.h"

#define MAXTIMEHITTING PI / 2
#define ARMLENGTH 0.75f

class Player {
public:
	slot craftSlots[5];
	slot benchCraftSlots[10];
	glm::vec3 position, forward, right, up, front;
	bool jumping;
	float jumpingSpeed;
	float settingBlock;
	bool keys[1024];
	slot slots[24];
	slot buf;
	int bufslot;
	int currslot=0;
	bool isCraft;
	float health;
	float timeLastHit;

	Player(World *world);

	void doMovement(World *world, bool isOpenedInterface, SocketTCP *socket);

	void addToInventory(int num, int id);
	int decFromInventory(int num, int numslot);

	void processControls();

	bool isChangedPos();
private:
	glm::vec3 oldPos;
};