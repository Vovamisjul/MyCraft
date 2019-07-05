#include "DrawPlayer.h"

void DrawPlayer::Draw(NetPlayer *otherplayer, Player *player)
{
	glm::vec3 left = glm::normalize(glm::cross(otherplayer->lookingbody, glm::vec3(0.0f, 1.0f, 0.0f)));
	head->Draw(otherplayer, player);
	body->Draw(otherplayer, player);
	otherplayer->positionLeg = otherplayer->position + left * 0.125f - glm::vec3(0.0f, 0.75f, 0.0f);
	otherplayer->movingCurrLeg = otherplayer->movingLeg;
	leg->Draw(otherplayer, player);
	otherplayer->positionLeg = otherplayer->position - left * 0.125f - glm::vec3(0.0f, 0.75f, 0.0f);
	otherplayer->movingCurrLeg = -otherplayer->movingLeg;
	leg->Draw(otherplayer, player);
	otherplayer->positionLeg = otherplayer->position + left * 0.375f;
	otherplayer->movingCurrLeg = -otherplayer->movingLeg;
	otherplayer->isRight = true;
	arm->Draw(otherplayer, player);
	otherplayer->positionLeg = otherplayer->position - left * 0.375f;
	otherplayer->movingCurrLeg = otherplayer->movingLeg;
	otherplayer->isRight = false;
	arm->Draw(otherplayer, player);

}