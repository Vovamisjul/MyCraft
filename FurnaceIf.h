#pragma once
#include "Shader.h"
#include "Player.h"
class FurnaceIf : public Shader {
public:
	GLuint texInv;
	FurnaceIf(const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(GLuint *texturesInv, GLuint *texturesNum, Player *player, Furnace *furnace);
private:
	float vertices[20] = {
		// Positions          // Colors           // Texture Coords
		1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // Top Right
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOinv[24], VBOinv[24];

	float verticesInv[20] = {
		// Positions          // Colors           // Texture Coords
		-0.35f,  0.07f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.35f, -0.11f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.48f, -0.11f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.48f,  0.07f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOinvnum[2][24], VBOinvnum[2][24];

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

	GLuint VAOinvcraft[3], VBOinvcraft[3];

	float craftVerticesInv[3][20] = {
		// Positions          // Colors           // Texture Coords
		-0.1375f, 0.77f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1375f, 0.58f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.2675f, 0.58f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.2675f, 0.77f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.1375f, 0.39f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1375f, 0.20f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.2675f, 0.20f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.2675f, 0.39f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.18125f, 0.58f, 0.0f,  1.0f, 1.0f, // Top Right
		0.18125f, 0.39f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		0.05125f, 0.39f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.05125f, 0.58f, 0.0f,   0.0f, 1.0f,  // Top Left 
	};


	GLuint VAOinvcraftnum[2][3], VBOinvcraftnum[2][3];
	float craftVerticesInvNum[2][3][20] = {
		// Positions          // Colors           // Texture Coords
		-0.1375f, 0.62f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1375f, 0.58f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.1675f, 0.58f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.1675f, 0.62f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.1375f, 0.24f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1375f, 0.20f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.1675f, 0.20f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.1675f, 0.24f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.18125f, 0.43f, 0.0f,  1.0f, 1.0f, // Top Right
		0.18125f, 0.39f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		0.15125f, 0.39f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.15125f, 0.43f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.1675f, 0.62f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1675f, 0.58f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.1975f, 0.58f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.1975f, 0.62f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.1675f, 0.24f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1675f, 0.20f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.1975f, 0.20f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.1975f, 0.24f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.15125f, 0.43f, 0.0f,  1.0f, 1.0f, // Top Right
		0.15125f, 0.39f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		0.12125f, 0.39f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.12125f, 0.43f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOprcburn[3], VBOprcburn[3];

	float craftVerticesPrcBurn[20] = {
		-0.1375f, 0.43f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.1375f, 0.39f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.1675f, 0.39f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.1675f, 0.43f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOprcmelt[3], VBOprcmelt[3];

	float craftVerticesPrcMelt[20] = {
		0.0f, 0.62f, 0.0f,  1.0f, 1.0f, // Top Right
		0.0f, 0.58f, 0.0f,  1.0f, 0.0f, // Bottom Right 
		-0.03f, 0.58f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.03f, 0.62f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	int indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	int width, height;

	void initialize();
	void initializeInv();
	void initializeInvNum();
	void initializeInvCraft();
	void initializeInvCraftNum();
	void initializePrcBurn();
	void initializePrcMelt();
	void drawInv(GLuint *texturesInv, GLuint *texturesNum, Player *player, Furnace *furnace);
	void drawInvNum(GLuint *texturesNums, Player *player, Furnace *furnace);
	void drawNum(GLuint *texturesNums, Furnace *furnace);
	void drawPrcBurn(GLuint *texturesNum, Furnace *furnace);
	void drawPrcMelt(GLuint *texturesNum, Furnace *furnace);

};