#include "HPBar.h"
#include <stb_image.h>
#include <SOIL.h>

HPBar::HPBar(const GLchar* vertexPath, const GLchar* fragmentPath) : Shader::Shader(vertexPath, fragmentPath)
{
	initialize();
}

void HPBar::initialize()
{
	for (int i = 0; i < 4; i++)
	{
		glGenVertexArrays(1, &VAOHP[i]);
		glGenBuffers(1, &VBOHP[i]);
		glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAOHP[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBOHP[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);

		vertices[0] += 0.075f;
		vertices[5] += 0.075f;
		vertices[10] += 0.075f;
		vertices[15] += 0.075f;
	}
}

void HPBar::draw(GLuint *texturesNum, Player *player)
{
	glDepthFunc(GL_LESS); // set depth f*
	Use();
	glActiveTexture(GL_TEXTURE0);
	int health = player->health;
	int i = 0;
	int divider = 100;
	int digit;
	while (divider > 0)
	{
		digit = health / divider;
		if (!(i == 0 && digit == 0))
		{
			glBindTexture(GL_TEXTURE_2D, texturesNum[digit]);
			glBindVertexArray(VAOHP[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			i++;
		}
		health = health % divider;
		divider = divider / 10;
	}

	glBindTexture(GL_TEXTURE_2D, texturesNum[10]);
	glBindVertexArray(VAOHP[i]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}