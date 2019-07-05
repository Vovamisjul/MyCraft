#pragma once
#include "shader.h"

class OnCursor : public Shader
{
public:
	OnCursor(const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(float x, float y, int texture, GLuint *textureNum, int num);
private:

	float cursorVerticesInv[20] = {
		// Positions          // Colors           // Texture Coords
		0.065f, 0.09f, 0.0f,  1.0f, 1.0f, // Top Right
		0.065f, -0.09f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.065f, -0.09f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.065f, 0.09f, 0.0f,   0.0f, 1.0f  // Top Left 
	};


	GLuint VAOinvnum[2], VBOinvnum[2], EBOinvnum[2];

	float cursorVerticesNum[2][20] = {
		// Positions          // Colors           // Texture Coords
		0.065f, -0.05f, 0.0f,  1.0f, 1.0f, // Top Right
		0.065f, -0.09f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		0.035f, -0.09f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.035f, -0.05f, 0.0f,   0.0f, 1.0f,  // Top Left 
		0.035f, -0.05f, 0.0f,  1.0f, 1.0f, // Top Right
		0.035f, -0.09f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		0.005f, -0.09f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.005f, -0.05f, 0.0f,   0.0f, 1.0f  // Top Left 
	}; 

	int indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	void initialize();
	void initializeNum();
};