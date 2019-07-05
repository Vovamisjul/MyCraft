#include "Body.h"

Body::Body(string path, const GLchar* vertexPath, const GLchar* fragmentPath) : CommonPlayer::CommonPlayer(path, vertexPath, fragmentPath)
{

}

void Body::Draw(NetPlayer *otherplayer, Player *player)
{
	glDepthFunc(GL_LEQUAL);

	glFrontFace(GL_CCW);
	Use();
	setMat4("projection", projection);
	model = glm::mat4(1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 left = glm::normalize(glm::cross(otherplayer->lookingbody, up));
	glm::vec3 front = glm::normalize(glm::cross(left, up));
	model = glm::translate(model, otherplayer->position - glm::vec3(0.0f, 0.75f, 0.0f));
	model = glm::rotate(model, -PI / 2, left);
	model = glm::rotate(model, -PI / 2, front);
	if (otherplayer->lookingbody.z < 0)
		model = glm::rotate(model, atan(otherplayer->lookingbody.x / otherplayer->lookingbody.z), up);
	else
		model = glm::rotate(model, atan(otherplayer->lookingbody.x / otherplayer->lookingbody.z) + PI, up);
	model = glm::scale(model, glm::vec3(0.5f));
	setMat4("model", model);

	glm::mat4 view = glm::lookAt(player->position, player->position + player->front, player->up);
	setMat4("view", view);

	DrawVertices(this);

	glFrontFace(GL_CW);
}