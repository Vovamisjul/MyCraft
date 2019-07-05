#include "Inhand.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <SOIL.h>

Inhand::Inhand(const GLchar* vertexPath, const GLchar* fragmentPath) : Shader::Shader(vertexPath, fragmentPath)
{
	initialize();
}

void Inhand::initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(inventoryVertices), &inventoryVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
}

void Inhand::draw(Player *player, GLuint *texture, World *world)
{
	Use();
	left = glm::normalize(glm::cross(player->front, player->up));
	up = glm::normalize(glm::cross(left, player->front));
	view = glm::lookAt(player->position, player->position + player->front, player->up);
	model = glm::mat4(1.0f);
	if (player->settingBlock < 0.2)
	{
		model = glm::translate(model, player->position + (sinf(player->settingBlock * 3 * PI) + 0.5f) * player->front - (0.3f + player->settingBlock * 2)*up + 0.8f*left);
	}
	else
		model = glm::translate(model, player->position + player->front - (0.5f)*up + 0.8f*left);
	if (player->front.z < 0)
		model = glm::rotate(model, atan(player->front.x / player->front.z), up);
	else
		model = glm::rotate(model, atan(player->front.x / player->front.z) + 3.141595f, up);
	model = glm::rotate(model, atan(player->front.y / sqrt(player->front.z*player->front.z + player->front.x*player->front.x)), left);
	if (player->settingBlock < 0.2)
	{
		player->settingBlock += world->deltaTime * 0.7;
		model = glm::rotate(model, -player->settingBlock * 4, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -0.1f, up);
	}

	setMat4("projection", projection);
	setMat4("view", view);
	setMat4("model", model);
	setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	setVec3("lightPos", 0.0f, 100.0f, 0.0f);
	// skybox cube
	glDepthFunc(GL_ALWAYS);  // change depth function so depth test passes when values are equal to depth buffer's content
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture[player->slots[player->currslot].id]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

/*void Inhand::drawkek(player *Player, GLuint *texture, world *World)
{
	glDepthFunc(GL_ALWAYS);  // change depth function so depth test passes when values are equal to depth buffer's content
	for (int i = 0; i < 97; i++)
	{
		Use();
		left = glm::normalize(glm::cross(Player->front, Player->up));
		up = glm::normalize(glm::cross(left, Player->front));
		view = glm::lookAt(Player->position, Player->position + Player->front, Player->up);
		model = glm::mat4(1.0f);
		if (Player->settingBlock < 0.2)
		{
			if (i < 39)
				model = glm::translate(model, Player->position + (sinf(Player->settingBlock * 3 * PI) + 0.5f) *(((i + 1) / 2)*0.02f + 1)*Player->front - (0.3f + Player->settingBlock * 2)*(1 - (i / 2) * 0.04f)*(0.5f)*up + 0.8f*left);
			else
				if (i < 58)
					model = glm::translate(model, Player->position + (sinf(Player->settingBlock * 3 * PI) + 0.5f) *(((i - 39))*0.02f + 1)*Player->front - (0.3f + Player->settingBlock * 2)*(1 - ((i - 39) + 1) * 0.04f)*(0.5f)*up + 0.8f*left);
				else
					model = glm::translate(model, Player->position + (sinf(Player->settingBlock * 3 * PI) + 0.5f) *(((i - 58 + 1) / 2 - 1)*0.02f + 1)*Player->front - (0.3f + Player->settingBlock * 2)*(1 - ((i - 58 + 1) / 2 + 1) * 0.04f)*(0.5f)*up + 0.8f*left);
		}
		else
		{
			if (i < 39)
				model = glm::translate(model, Player->position + (((i + 1) / 2)*0.02f + 1)*Player->front - (1 - (i / 2) * 0.04f)*(0.5f)*up + 0.8f*left);
			else
				if (i < 58)
					model = glm::translate(model, Player->position + (((i - 39))*0.02f + 1)*Player->front - (1 - ((i - 39) + 1) * 0.04f)*(0.5f)*up + 0.8f*left);
				else
					model = glm::translate(model, Player->position + (((i - 58 + 1) / 2 - 1)*0.02f + 1)*Player->front - (1 - ((i - 58 + 1) / 2 + 1) * 0.04f)*(0.5f)*up + 0.8f*left);
		}
		if (Player->front.z < 0)
			model = glm::rotate(model, atan(Player->front.x / Player->front.z), up);
		else
			model = glm::rotate(model, atan(Player->front.x / Player->front.z) + 3.141595f, up);
		model = glm::rotate(model, atan(Player->front.y / sqrt(Player->front.z*Player->front.z + Player->front.x*Player->front.x)), left);
		if (Player->settingBlock < 0.2)
		{
			Player->settingBlock += World->deltaTime * 0.7;
		}
		modelLoc = glGetUniformLocation(Program, "model");
		viewLoc = glGetUniformLocation(Program, "view");
		projLoc = glGetUniformLocation(Program, "projection");
		// Pass them to the shaders
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// skybox cube
		glBindVertexArray(pixVAO);
		if (i<39)
			glBindTexture(GL_TEXTURE_CUBE_MAP, texturesStick[0]);
		else
			if (i<58)
				glBindTexture(GL_TEXTURE_CUBE_MAP, texturesStick[1]);
			else
				glBindTexture(GL_TEXTURE_CUBE_MAP, texturesStick[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
}*/