#pragma once
#include <glm/glm.hpp>
#include "Const.h"

class NetPlayer {
public:
	glm::vec3 position;
	glm::vec3 positionLeg;
	glm::vec3 looking;
	glm::vec3 lookingbody;
	float movingLeg;
	float movingCurrLeg;
	float timeHitting;
	bool going;
	bool hitting;
	bool isRight;
	char blockType;
	char id;
	NetPlayer(glm::vec3 position, glm::vec3 looking, int id);
	NetPlayer();
};