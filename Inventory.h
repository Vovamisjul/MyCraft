#pragma once
#include "Shader.h"
#include "Player.h"

class Inventory : public Shader {
public:
	GLuint texInv;
	Inventory(const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw();
	void drawInv(GLuint *texturesInv, GLuint *texturesNum, Player *player);
	void drawInvNum(GLuint *texturesNums, Player *player);
private:
	float vertices[20] = {
		// Positions          // Colors           // Texture Coords
		1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOinv[24], VBOinv[24], EBOinv[24];

	float verticesInv[20] = {
		// Positions          // Colors           // Texture Coords
		-0.35f,  0.07f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.35f, -0.11f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.48f, -0.11f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.48f,  0.07f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOinvnum[2][24], VBOinvnum[2][24], EBOinvnum[2][24];

	float numVerticesInv[2][20] = {
		// Positions          // Colors           // Texture Coords
		-0.36f,  -0.07f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.36f, -0.11f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.39f, -0.11f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.39f,  -0.07f, 0.0f,   0.0f, 1.0f,  // Top Left 
		-0.39f,  -0.07f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.39f, -0.11f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.42f, -0.11f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.42f,  -0.07f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOinvcraft[5], VBOinvcraft[5], EBOinvcraft[5];

	float craftVerticesInv[20] = {
		// Positions          // Colors           // Texture Coords
		-0.35f, 0.57f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.35f, 0.38f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.48f, 0.38f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.48f, 0.57f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	

	int indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	int width, height;

	void initialize();
	void initializeInv();
	void initializeInvCraft();
	void initializeInvNum();
};