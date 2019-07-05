#pragma once
#include "glew.h"
#include "Shader.h"
#include "Player.h"
class MinInventory : public Shader {
public:
	GLuint texMinInv;
	GLuint textureinv[256];
	GLuint texturenum[11];
	MinInventory(const GLchar* vertexPath, const GLchar* fragmentPath);
	void draw(Player *player);
private:
	float mininvVertices[20] = {
		// Positions          // Colors           // Texture Coords
		0.515f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		0.515f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.515f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.515f,  -0.65f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	int indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	int width, height;
	GLuint VAOinv[7], VBOinv[7], EBOinv[7];
	float icinvVertices[7][20] = {
		// Positions          // Colors           // Texture Coords
		-0.334f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.334f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.502f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.502f,  -0.65f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.193f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.193f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.360f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.360f,  -0.65f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.054f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.054f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.221f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.221f,  -0.65f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.083f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		0.083f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.083f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.083f,  -0.65f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.221f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		0.221f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.054f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.054f,  -0.65f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.360f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		0.360f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.193f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.193f,  -0.65f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.502f,  -0.65f, 0.0f,  1.0f, 1.0f, // Top Right
		0.502f, -0.9f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.334f, -0.9f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.334f,  -0.65f, 0.0f,   0.0f, 1.0f  // Top Left 
	};


	GLuint VAOnum[7], VBOnum[7], EBOnum[7];

	float icnumVertices[7][20] = {
		// Positions          // Colors           // Texture Coords
		-0.334f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.334f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.418f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.418f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.193f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.193f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.276f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.276f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.054f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.054f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.137f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.137f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.083f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.083f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.0f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.0f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.221f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.221f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.137f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.137f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.360f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.360f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.276f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.276f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.502f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.502f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.418f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.418f,  -0.75f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLuint VAOnumOld[7], VBOnumOld[7], EBOnumOld[7];

	float icnumVerticesOld[7][20] = {
		// Positions          // Colors           // Texture Coords
		-0.398f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.398f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.482f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.482f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.256f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.256f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.340f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.340f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		-0.117f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		-0.117f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.201f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.201f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.02f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.02f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.063f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.063f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.157f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.157f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.074f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.074f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.296f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.296f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.213f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.213f,  -0.75f, 0.0f,   0.0f, 1.0f,  // Top Left 

		0.438f,  -0.75f, 0.0f,  1.0f, 1.0f, // Top Right
		0.438f, -0.85f, 0.0f,  1.0f, 0.0f, // Bottom Right
		0.354f, -0.85f, 0.0f,  0.0f, 0.0f, // Bottom Left
		0.354f,  -0.75f, 0.0f,   0.0f, 1.0f  // Top Left 
	};


	void initializenum();
	void drawnum(int num, int slot);

	char* texpath[NUMBLOCKS] = { 
		"textures/009.png", "textures/019.png", "textures/029.png", "textures/039.png", "textures/049.png", 
		"textures/059.png", "textures/069.png", "textures/079.png", "textures/089.png", "textures/099.png", 
		"textures/009.png", "textures/009.png", "textures/009.png", "textures/009.png", "textures/009.png",
		"textures/159.png", "textures/009.png", "textures/179.png" ,"textures/189.png" ,"textures/009.png",
		"textures/209.png", "textures/219.png", "textures/009.png" };
	char *texpathNotBlocks[NUMNOTBLOCKS] = {
		"textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png",
		"textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png", "textures/3d/2ds/diamond/diamond.png" };

	char *texpathInstruments[NUMINSTRUMENTS] = {
		"textures/3d/pickaxes/diamond/diamond_pickaxe.png", "textures/3d/axes/diamond/diamond_axe.png", "textures/3d/pickaxes/diamond/diamond_pickaxe.png" };
	char* texpathnum[11] = { "textures/numbers/0.png", "textures/numbers/1.png", "textures/numbers/2.png", "textures/numbers/3.png", "textures/numbers/4.png",
							 "textures/numbers/5.png", "textures/numbers/6.png", "textures/numbers/7.png", "textures/numbers/8.png", "textures/numbers/9.png", 
							 "textures/numbers/%.png" };
	void initialize();
	void initializeimg();
};