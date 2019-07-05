#pragma once
#include "shader.h"
#include "glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"
class Cursor : public Shader {
public:
	Cursor(const GLchar* vertexPath, const GLchar* fragmentPath);
	GLuint texCursor;
	void draw();
private:
	float cursorVertices[20] = {
		// Positions          // Colors           // Texture Coords
		0.015f,  0.025f, 0.0f,  1.0f, 1.0f, // Top Right
		0.015f, -0.025f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-0.015f, -0.025f, 0.0f,  0.0f, 0.0f, // Bottom Left
		-0.015f,  0.025f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	int indices[6] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	int width, height;
	void initialize();
};