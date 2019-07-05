#include "FurnaceIf.h"
#include <stb_image.h>
#include <SOIL.h>

FurnaceIf::FurnaceIf(const GLchar* vertexPath, const GLchar* fragmentPath) : Shader::Shader(vertexPath, fragmentPath)
{
	initialize();
}

void FurnaceIf::initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);


	glGenTextures(1, &texInv);
	glBindTexture(GL_TEXTURE_2D, texInv); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
										  // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load image, create texture and generate mipmaps
	unsigned char* image = SOIL_load_image("textures/interface/furnace.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Un

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);

	initializeInv();
	initializeInvNum();
	initializeInvCraft();
	initializeInvCraftNum();
	initializePrcBurn();
	initializePrcMelt();
}

void FurnaceIf::initializeInv()
{
	for (int i = 0; i < 24; i++)
	{
		glGenVertexArrays(1, &VAOinv[i]);
		glGenBuffers(1, &VBOinv[i]);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAOinv[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOinv[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesInv), verticesInv, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);

		if (((i + 1) % 8) != 0)
		{
			verticesInv[0] += 0.10625f;
			verticesInv[5] += 0.10625f;
			verticesInv[10] += 0.10625f;
			verticesInv[15] += 0.10625f;
		}
		else
		{
			verticesInv[0] = verticesInv[5] = -0.35f;
			verticesInv[10] = verticesInv[15] = -0.48f;
			verticesInv[1] -= 0.188889f;
			verticesInv[6] -= 0.188889f;
			verticesInv[11] -= 0.188889f;
			verticesInv[16] -= 0.188889f;
		}
	}
}

void FurnaceIf::initializeInvNum()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 24; i++)
		{
			glGenVertexArrays(1, &VAOinvnum[j][i]);
			glGenBuffers(1, &VBOinvnum[j][i]);
			// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
			glBindVertexArray(VAOinvnum[j][i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBOinvnum[j][i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(numVerticesInv[j]), numVerticesInv[j], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glBindVertexArray(0);

			if (((i + 1) % 8) != 0)
			{
				numVerticesInv[j][0] += 0.10625f;
				numVerticesInv[j][5] += 0.10625f;
				numVerticesInv[j][10] += 0.10625f;
				numVerticesInv[j][15] += 0.10625f;
			}
			else
			{
				if (j == 0)
				{
					numVerticesInv[j][0] = numVerticesInv[j][5] = -0.36f;
					numVerticesInv[j][10] = numVerticesInv[j][15] = -0.39f;
				}
				if (j == 1)
				{
					numVerticesInv[j][0] = numVerticesInv[j][5] = -0.39f;
					numVerticesInv[j][10] = numVerticesInv[j][15] = -0.42f;
				}
				numVerticesInv[j][1] -= 0.188889f;
				numVerticesInv[j][6] -= 0.188889f;
				numVerticesInv[j][11] -= 0.188889f;
				numVerticesInv[j][16] -= 0.188889f;
			}
		}
	}
}

void FurnaceIf::initializeInvCraft()
{
	for (int i = 0; i < 3; i++)
	{
		glGenVertexArrays(1, &VAOinvcraft[i]);
		glGenBuffers(1, &VBOinvcraft[i]);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAOinvcraft[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOinvcraft[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(craftVerticesInv[i]), craftVerticesInv[i], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
}

void FurnaceIf::initializeInvCraftNum()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			glGenVertexArrays(1, &VAOinvcraftnum[j][i]);
			glGenBuffers(1, &VBOinvcraftnum[j][i]);
			// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
			glBindVertexArray(VAOinvcraftnum[j][i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBOinvcraftnum[j][i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(craftVerticesInvNum[j][i]), craftVerticesInvNum[j][i], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glBindVertexArray(0);
		}
	}
}

void FurnaceIf::initializePrcBurn()
{
	for (int i = 0; i < 3; i++)
	{
		glGenVertexArrays(1, &VAOprcburn[i]);
		glGenBuffers(1, &VBOprcburn[i]);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAOprcburn[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOprcburn[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(craftVerticesPrcBurn), craftVerticesPrcBurn, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);


		craftVerticesPrcBurn[0] -= 0.03f;
		craftVerticesPrcBurn[5] -= 0.03f;
		craftVerticesPrcBurn[10] -= 0.03f;
		craftVerticesPrcBurn[15] -= 0.03f;
	}
}

void FurnaceIf::initializePrcMelt()
{
	for (int i = 0; i < 3; i++)
	{
		glGenVertexArrays(1, &VAOprcmelt[i]);
		glGenBuffers(1, &VBOprcmelt[i]);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAOprcmelt[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOprcmelt[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(craftVerticesPrcMelt), craftVerticesPrcMelt, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);


		craftVerticesPrcMelt[0] -= 0.03f;
		craftVerticesPrcMelt[5] -= 0.03f;
		craftVerticesPrcMelt[10] -= 0.03f;
		craftVerticesPrcMelt[15] -= 0.03f;
	}
}

void FurnaceIf::draw(GLuint *texturesInv, GLuint *texturesNum, Player *player, Furnace *furnace)
{
	glDepthFunc(GL_LESS); // set depth f*
	Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texInv);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	drawInv(texturesInv, texturesNum, player, furnace);
	drawNum(texturesNum, furnace);
	drawPrcBurn(texturesNum, furnace);
	drawPrcMelt(texturesNum, furnace);
}

void FurnaceIf::drawInv(GLuint *texturesInv, GLuint *texturesNum, Player *player, Furnace *furnace)
{
	glDepthFunc(GL_LEQUAL); // set depth f*
	for (int i = 0; i < 24; i++)
	{
		if (player->slots[i].num)
		{
			Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturesInv[player->slots[i].id]);
			glBindVertexArray(VAOinv[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			drawInvNum(texturesNum, player, furnace);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (furnace->slots[i].num)
		{
			Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturesInv[furnace->slots[i].id]);
			glBindVertexArray(VAOinvcraft[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			drawInvNum(texturesNum, player, furnace);
		}
	}
}

void FurnaceIf::drawInvNum(GLuint *texturesNum, Player *player, Furnace *furnace)
{
	for (int i = 0; i < 24; i++)
	{
		if (player->slots[i].num)
		{
			glDepthFunc(GL_LEQUAL);
			if (player->slots[i].num >= 10)
			{
				Use();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texturesNum[player->slots[i].num / 10]);
				glBindVertexArray(VAOinvnum[1][i]);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
			Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturesNum[player->slots[i].num % 10]);
			glBindVertexArray(VAOinvnum[0][i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}

void FurnaceIf::drawNum(GLuint *texturesNums, Furnace *furnace)
{
	for (int i = 0; i < 3; i++)
	{
		if (furnace->slots[i].num)
		{
			glDepthFunc(GL_LEQUAL);
			if (furnace->slots[i].num >= 10)
			{
				Use();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texturesNums[furnace->slots[i].num / 10]);
				glBindVertexArray(VAOinvcraftnum[1][i]);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
			Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturesNums[furnace->slots[i].num % 10]);
			glBindVertexArray(VAOinvcraftnum[0][i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}

void FurnaceIf::drawPrcBurn(GLuint *texturesNum, Furnace *furnace)
{
	int prc = furnace->givePrcBurn();
	if (prc == 100)
		prc = 99;
	if (prc)
	{
		glDepthFunc(GL_LEQUAL);
		if (prc >= 10)
		{
			Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturesNum[prc / 10]);
			glBindVertexArray(VAOprcburn[2]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturesNum[prc % 10]);
		glBindVertexArray(VAOprcburn[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturesNum[10]);
		glBindVertexArray(VAOprcburn[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void FurnaceIf::drawPrcMelt(GLuint *texturesNum, Furnace *furnace)
{
	int prc = furnace->givePrcMelt();
	if (prc == 100)
		prc = 99;
	if (prc)
	{
		glDepthFunc(GL_LEQUAL);
		if (prc >= 10)
		{
			Use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturesNum[prc / 10]);
			glBindVertexArray(VAOprcmelt[2]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturesNum[prc % 10]);
		glBindVertexArray(VAOprcmelt[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturesNum[10]);
		glBindVertexArray(VAOprcmelt[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}