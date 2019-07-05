#include "NetPlayer.h"

NetPlayer::NetPlayer(glm::vec3 position, glm::vec3 looking, int id)
{
	this->position = position;
	this->lookingbody = this->looking = position;
	movingLeg = 3 * PI;
	going = false;
	this->id = id;
	hitting = false;
	timeHitting = 0;
}

NetPlayer::NetPlayer()
{

}