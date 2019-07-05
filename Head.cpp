#include "Head.h"

Head::Head(string path, const GLchar* vertexPath, const GLchar* fragmentPath) : CommonPlayer::CommonPlayer(path, vertexPath, fragmentPath)
{

}

void Head::Draw(NetPlayer *otherplayer, Player *player)
{
	glDepthFunc(GL_LEQUAL);

	glFrontFace(GL_CCW);
	Use();
	setMat4("projection", projection);
	model = glm::mat4(1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 left = glm::normalize(glm::cross(otherplayer->looking, up));
	model = glm::translate(model, otherplayer->position);
	model = glm::rotate(model, -PI / 2, left);
	model = glm::rotate(model, atan(otherplayer->looking.y / sqrt(otherplayer->looking.z*otherplayer->looking.z + otherplayer->looking.x*otherplayer->looking.x)), left);
	if (otherplayer->looking.z < 0)
		model = glm::rotate(model, atan(otherplayer->looking.x / otherplayer->looking.z), up);
	else
		model = glm::rotate(model, atan(otherplayer->looking.x / otherplayer->looking.z) + PI, up);
	model = glm::scale(model, glm::vec3(0.5f));
	setMat4("model", model);

	glm::mat4 view = glm::lookAt(player->position, player->position + player->front, player->up);
	setMat4("view", view);

	DrawVertices(this);

	glFrontFace(GL_CW);
}