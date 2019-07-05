#pragma once
#include "Shader.h"
#include "Player.h"
class HPBar : public Shader {
public:
	GLuint texInv;
	HPBar(const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(GLuint *texturesNum, Player *player);
private:
	float vertices[20] = {
		// Positions          // Colors           // Texture Coords
		-0.4f, -0.45f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.4f, -0.6f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.515f, -0.6f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.515f, -0.45f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	int indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint VAOHP[4], VBOHP[4];
	void initialize();
};