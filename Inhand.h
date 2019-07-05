#pragma once
#include "Shader.h"
#include "Player.h"
class Inhand : public Shader {
public:
	Inhand(const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(Player *player, GLuint *texture, World *world);
private:
	glm::vec3 left, up;
	float inventoryVertices[108] = {
		// positions      
		-0.3f,  0.3f, -0.3f,
		-0.3f, -0.3f, -0.3f,
		0.3f, -0.3f, -0.3f,
		0.3f, -0.3f, -0.3f,
		0.3f,  0.3f, -0.3f,
		-0.3f,  0.3f, -0.3f,

		-0.3f, -0.3f,  0.3f,
		-0.3f, -0.3f, -0.3f,
		-0.3f,  0.3f, -0.3f,
		-0.3f,  0.3f, -0.3f,
		-0.3f,  0.3f,  0.3f,
		-0.3f, -0.3f,  0.3f,

		0.3f, -0.3f, -0.3f,
		0.3f, -0.3f,  0.3f,
		0.3f,  0.3f,  0.3f,
		0.3f,  0.3f,  0.3f,
		0.3f,  0.3f, -0.3f,
		0.3f, -0.3f, -0.3f,

		-0.3f, -0.3f,  0.3f,
		-0.3f,  0.3f,  0.3f,
		0.3f,  0.3f,  0.3f,
		0.3f,  0.3f,  0.3f,
		0.3f, -0.3f,  0.3f,
		-0.3f, -0.3f,  0.3f,

		-0.3f,  0.3f, -0.3f,
		0.3f,  0.3f, -0.3f,
		0.3f,  0.3f,  0.3f,
		0.3f,  0.3f,  0.3f,
		-0.3f,  0.3f,  0.3f,
		-0.3f,  0.3f, -0.3f,

		-0.3f, -0.3f, -0.3f,
		-0.3f, -0.3f,  0.3f,
		0.3f, -0.3f, -0.3f,
		0.3f, -0.3f, -0.3f,
		-0.3f, -0.3f,  0.3f,
		0.3f, -0.3f,  0.3f
	};
	void initialize();
};