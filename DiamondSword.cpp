#include "DiamondSword.h"

DiamondSword::DiamondSword(string path, const GLchar* vertexPath, const GLchar* fragmentPath) : CommonModel::CommonModel(path, vertexPath, fragmentPath)
{

}

void DiamondSword::draw(Player *player, World *world)
{

	glDepthFunc(GL_LEQUAL);

	glFrontFace(GL_CCW);
	Use();
	setMat4("projection", projection);
	glm::vec3 left = glm::normalize(glm::cross(player->front, player->up));
	glm::vec3 up = glm::normalize(glm::cross(left, player->front));
	glm::mat4 model = glm::mat4(1.0f);
	if (player->settingBlock < 0.2)
	{
		model = glm::translate(model, player->position + (sinf(player->settingBlock * PI) + 0.5f) * player->front - (0.3f + player->settingBlock * 2)*up + (0.8f - player->settingBlock * 2)*left);
	}
	else
		model = glm::translate(model, player->position + (0.8f) * player->front - (0.5f)*up + 0.6f*left);
	if (player->front.z < 0)
		model = glm::rotate(model, atan(player->front.x / player->front.z), up);
	else
		model = glm::rotate(model, atan(player->front.x / player->front.z) + PI, up);
	model = glm::rotate(model, atan(player->front.y / sqrt(player->front.z*player->front.z + player->front.x*player->front.x)), left);
	if (player->settingBlock < 0.2)
	{
		player->settingBlock += world->deltaTime * 0.7;
		model = glm::rotate(model, -player->settingBlock * 2, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -0.15f, up);
	}
	model = glm::rotate(model, -PI / 2, player->up);
	model = glm::scale(model, glm::vec3(0.05f));
	setMat4("model", model);

	glm::mat4 view = glm::lookAt(player->position, player->position + player->front, player->up);
	setMat4("view", view);

	DrawVertices(this);

	glFrontFace(GL_CW);
}

void DiamondSword::drawInNetPlayer(Player *player, NetPlayer *netPlayer, World *world)
{

	glDepthFunc(GL_LEQUAL);

	glFrontFace(GL_CCW);
	Use();
	setMat4("projection", projection);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 left = glm::normalize(glm::cross(netPlayer->lookingbody, up));
	glm::mat4 model = glm::mat4(1.0f);


	if (netPlayer->hitting || netPlayer->timeHitting > 0.0f && netPlayer->timeHitting <= MAXTIMEHITTING)
	{
		netPlayer->timeHitting += 4.0f * world->deltaTime;
	}
	if (netPlayer->timeHitting > MAXTIMEHITTING)
	{
		if (netPlayer->hitting)
			netPlayer->timeHitting -= MAXTIMEHITTING;
		else
			netPlayer->timeHitting = 0.0f;
	}

	if (netPlayer->timeHitting > 0.0f)
	{
		model = glm::translate(model, netPlayer->position + (cosf(netPlayer->timeHitting) * ARMLENGTH + 0.4f) * netPlayer->lookingbody - ((sinf(netPlayer->timeHitting) - 1) * ARMLENGTH)*up + 0.4f*left);
	}
	else
	{
		model = glm::translate(model, netPlayer->position + (-sinf(sinf(netPlayer->movingLeg)) + 0.4f) * netPlayer->lookingbody - (cosf(sinf(netPlayer->movingLeg)) * ARMLENGTH)*up + 0.4f*left);

		//model = glm::translate(model, netPlayer->position + (sinf(MAXTIMEHITTING - sinf(netPlayer->movingCurrLeg) * MAXTIMEHITTING) * ARMLENGTH + 0.4f) * netPlayer->lookingbody - ((cosf(MAXTIMEHITTING - fabs(sinf(netPlayer->movingCurrLeg) * MAXTIMEHITTING)) - 1) * ARMLENGTH * 2)*up + 0.4f*left);

		//model = glm::translate(model, netPlayer->position + (0.4f) * netPlayer->lookingbody - (ARMLENGTH)*up + 0.4f*left);
	}
	if (netPlayer->lookingbody.z < 0)
		model = glm::rotate(model, atan(netPlayer->lookingbody.x / netPlayer->lookingbody.z), up);
	else
		model = glm::rotate(model, atan(netPlayer->lookingbody.x / netPlayer->lookingbody.z) + PI, up);
	if (netPlayer->timeHitting > 0.0f)
	{
		model = glm::rotate(model, MAXTIMEHITTING - netPlayer->timeHitting, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else
	{
		//model = glm::rotate(model, -sinf(netPlayer->movingLeg), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	model = glm::rotate(model, -PI / 2, up);
	model = glm::scale(model, glm::vec3(0.05f));
	setMat4("model", model);

	glm::mat4 view = glm::lookAt(player->position, player->position + player->front, player->up);
	setMat4("view", view);

	DrawVertices(this);

	glFrontFace(GL_CW);
}