#include "DiamondPickaxe.h"

DiamondPickaxe::DiamondPickaxe(string path, const GLchar* vertexPath, const GLchar* fragmentPath) : CommonModel::CommonModel(path, vertexPath, fragmentPath)
{

}

void DiamondPickaxe::draw(Player *player, World *world)
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
		model = glm::translate(model, player->position + (sinf(player->settingBlock * PI) + 0.5f) * player->front - (0.3f + player->settingBlock * 2)*up + (0.6f - player->settingBlock * 2)*left);
	}
	else
		model = glm::translate(model, player->position + (0.8f) * player->front - (0.5f)*up + 0.4f*left);
	if (player->front.z < 0)
		model = glm::rotate(model, atan(player->front.x / player->front.z), up);
	else
		model = glm::rotate(model, atan(player->front.x / player->front.z) + PI, up);
	model = glm::rotate(model, atan(player->front.y / sqrt(player->front.z*player->front.z + player->front.x*player->front.x)), left);
	if (player->settingBlock < 0.2)
	{
		player->settingBlock += world->deltaTime ;
		model = glm::rotate(model, -0.15f, up);
	}
	model = glm::rotate(model, -PI / 2, player->up);
	model = glm::scale(model, glm::vec3(0.04f));
	setMat4("model", model);

	glm::mat4 view = glm::lookAt(player->position, player->position + player->front, player->up);
	setMat4("view", view);

	DrawVertices(this);

	glFrontFace(GL_CW);
}

void DiamondPickaxe::drawInNetPlayer(Player *player, NetPlayer *netPlayer, World *World)
{

}