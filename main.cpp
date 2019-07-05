#define GLEW_STATIC
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "assimp-vc140-mt.lib")
#pragma comment(lib, "Ws2_32.lib")
#include <glew.h>
// GLFW
#include <glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/config.h>
#include <iostream>
#include <cstdlib> // для system
#include "Shader.h"
#include "const.h"
#include "World.h"
#include "Player.h"
#include "Functions.h"
#include "Control.h"
#include "CallBack.h"
#include "Skybox.h"
#include "Cursor.h"
#include "Inhand.h"
#include "MinInventory.h"
#include "Inventory.h"
#include "OnCursor.h"
#include "Mesh.h"
#include "Model.h"
#include "WorkBench.h"
#include "DiamondSword.h"
#include "DiamondAxe.h"
#include "DiamondPickaxe.h"
#include "DrawPlayer.h"
#include "FurnaceIf.h"
#include "SocketTCP.h"
#include "SocketUDP.h"
#include "Threads.h"
#include "HPBar.h"


GLfloat deltaTime = 0.0f;	
GLfloat lastFrame = 0.0f;


World *world;
Player *player;
Control *control;
bool endThreads = false;

void getTextureBroken(unsigned char *src, unsigned char *dest, int num, int numside)
{
	int height = num * 16;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 3; k++)
				dest[(i * 16 + j) * 3 + k] = src[((height + i) * 16 * 8 + numside * 16 + j) * 3 + k];
		}
}

void getTexture(unsigned char *src, unsigned char *dest, int num, int numside)
{
	int height = num * 16;
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 3; k++)
				dest[(i * 16 + j) * 3 + k] = src[((height + i) * 16 * 6 + numside * 16 + j) * 3 + k];
		}
}

void mergeWithBroken(unsigned char *broken, unsigned char *dest)
{
	for (int i = 0; i < 16 * 16 * 3; i++)
	{
		dest[i] &= broken[i];
	}
}

int main()
{
	char ip[30];
	int numport;
	printf_s("enter ip\n");
	gets_s(ip, 30);
	printf_s("enter port\n");
	scanf_s("%d", &numport);


	SocketTCP *socketTCP = new SocketTCP(ip, numport);
	SocketUDP *socketUDP = new SocketUDP(ip, numport);
	char messWorldGen[sizeof(int)];
	int resConnect = recv(socketTCP->sock, messWorldGen, sizeof(int), 0);
	int worldSeed;
	if (resConnect == -1)
	{
		worldSeed = 1;
		world = new World(worldSeed);
		player = new Player(world);
		control = new Control(player, world);
	}
	else
	{
		worldSeed = *((int*)messWorldGen);
		world = new World(worldSeed);
		player = new Player(world);
		control = new Control(player, world);
		Threads::StartRecieve(world, player, socketTCP->sock, socketUDP->sock, &endThreads);
	}
	control->socket = socketTCP;
	control->socketUdp = socketUDP;
	socketTCP->sendReqToNewChunk(world->currchank);
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Minecraft eto moya jizn", nullptr, nullptr);
	control->width = mode->width;
	control->height = mode->height;

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	// Set the required callback functions
	CallBack::Initialize(control);
	glfwSetKeyCallback(window, CallBack::Key);
	glfwSetCursorPosCallback(window, CallBack::Mouse);
	glfwSetMouseButtonCallback(window, CallBack::MouseButton);
	glfwSetScrollCallback(window, CallBack::Scroll);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glViewport(0, 0, control->width, control->height);



	Shader ourShader("shaders/vertex.txt", "shaders/fragment.txt");
	Skybox skyShader("shaders/skyvertex.txt", "shaders/skyfragment.txt");
	Cursor cursorShader("shaders/2dvertex.txt", "shaders/2dfragment.txt");
	Inhand inhandShader("shaders/vertex.txt", "shaders/fragment.txt");
	MinInventory mininvShader("shaders/2dvertex.txt", "shaders/2dfragment.txt");
	Inventory invShader("shaders/2dvertex.txt", "shaders/2dfragment.txt");
	OnCursor onCursorShader("shaders/oncursorvertex.txt", "shaders/oncursorfragment.txt");
	WorkBench workBenchShader("shaders/2dvertex.txt", "shaders/2dfragment.txt");
	FurnaceIf furnaceShader("shaders/2dvertex.txt", "shaders/2dfragment.txt");
	HPBar HPBarShader("shaders/2dvertex.txt", "shaders/2dfragment.txt");

	std::vector<CommonModel *> Models = { 
		new DiamondSword("textures/3d/swords/diamond/source/Diamond Sword.obj", "shaders/3dvertex.txt", "shaders/3dfragment.txt"),
		new DiamondAxe("textures/3d/axes/diamond/source/axe.fbx", "shaders/3dvertex.txt", "shaders/3dfragment.txt"),
		new DiamondPickaxe("textures/3d/pickaxes/diamond/source/pickaxe.fbx", "shaders/3dvertex.txt", "shaders/3dfragment.txt") };

	DrawPlayer *drawPlayer = new DrawPlayer();
	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {

		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f
	};
	int i;
	glEnable(GL_DEPTH_TEST);


	GLuint VBO, VAO;	  // Load and create a texture 
	GLuint texture[8][256];


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
		//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	unsigned char brokenData[8][16 * 16 * 3];
	unsigned char* broken = SOIL_load_image("textures/broken.png", &width, &height, 0, SOIL_LOAD_RGB);
	/*for (int i = 0; i < 200; i++)
		printf_s("%d: %d %d %d\n", i, broken[i*3], broken[i*3 + 1], broken[i*3 + 2]);*/
	for (int i = 0; i < 8; i++)
		getTextureBroken(broken, brokenData[i], 0, i);

	unsigned char data[16 * 16 * 3];
	unsigned char* img = SOIL_load_image("textures/blocks.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (img)
	{
		for (int j = 0; j < NUMBLOCKS; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				glGenTextures(1, &texture[k][j + 1]);
				glBindTexture(GL_TEXTURE_CUBE_MAP, texture[k][j + 1]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
					for (unsigned int i = 0; i < 6; i++)
					{
						getTexture(img, data, j, i);
						mergeWithBroken(brokenData[k], data);
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					}
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			}

		}
		SOIL_free_image_data(img);
	}
	else
	{
		std::cout << "Cubemap texture failed to load at path: " << "textures/blocks.png" << std::endl;
		SOIL_free_image_data(img);
	}
	ourShader.Use();
	ourShader.setInt("ourTexture", 0);
	//bool first = true;
	// Game loop
	int startChunk = world->currchank;
	int loadChunk = startChunk;
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(45.0f, (GLfloat)control->width / (GLfloat)control->height, 0.1f, 100.0f);
	GLint lightColorLoc = glGetUniformLocation(ourShader.ID, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(ourShader.ID, "lightPos");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, 0.0f, 100.0f, 0.0f);
	GLfloat setTime = 1;

	player->slots[0].id = instrumentType::WOODENPICKAXE;
	player->slots[0].num = 1;
	player->slots[1].id = instrumentType::WOODENAXE;
	player->slots[1].num = 1;
	player->slots[2].id = blocktype::FURNACE;
	player->slots[2].num = 1;
	lastFrame = glfwGetTime();


	NetPlayer *tmp = new NetPlayer();
	tmp->position = world->startpos;
	tmp->movingLeg = 0;
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		GLfloat currentFrame = glfwGetTime();
		world->deltaTime = currentFrame - lastFrame;
		if (world->deltaTime < 1 / 60)
			Sleep((1 / 60 - world->deltaTime)*1000);
		//std::cout << int(1/world->deltaTime) << std::endl;     //fps
		lastFrame = currentFrame;
		player->doMovement(world, control->showBench || control->showInv || control->showFurnace, socketTCP);
		if (player->isChangedPos())
			if (control->breakeBlock)
				control->startBreaking();
		// Render
		// Clear the colorbuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind Textures using texture units

		glDepthFunc(GL_LEQUAL);
		// Activate shader
		ourShader.Use();

		// Create transformations
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (GLfloat)glfwGetTime() * 2.0f, glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::lookAt(player->position, player->position + player->front, player->up);
		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(ourShader.ID, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.ID, "view");
		GLint projLoc = glGetUniformLocation(ourShader.ID, "projection");
		// Pass them to the shaders
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		for (int ch1 = -2; ch1 < 3; ch1++)
		{
			for (int ch2 = world->currchank - 2; ch2 < world->currchank + 3; ch2++)
			{
				int ch = ch2 - ch1*allChunks;
				int localchunk = ch2 + 2 - world->currchank + (ch1 + 2) * drawedChunks;
				for (GLuint i1 = 0; i1 < 64; i1++)
				{
					for (GLuint i2 = 0; i2 < 16 * 16; i2++)
					{
						if (world->toDraw[i1 * 16 * 16 + i2][localchunk])
						{
							//if (first) std::cout << (cubePositions[i].y * 16 * 16 + cubePositions[i].z * 16 + cubePositions[i].x) << endl;
							//for (int j = 0; j < 6; j++)
							//{
							model = glm::mat4(1.0f);
							model = glm::translate(model, world->cubePositions[i1 * 16 * 16 + i2] + glm::vec3(16.0f*(ch / allChunks), 0, 16.0*(ch % allChunks)));
							//model = glm::translate(model, cubePositions[i1 * 16 * 16 + i2]);
							glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
							//glActiveTexture(GL_TEXTURE0);
							glBindVertexArray(VAO);
							if (control->breakeBlock && (i1 * 16 * 16 + i2 == control->breakedBlock) && (ch == control->breakedChunk))
								glBindTexture(GL_TEXTURE_CUBE_MAP, texture[control->getTextureBroken()][world->blockType[i1 * 16 * 16 + i2][ch]]);
							else
								glBindTexture(GL_TEXTURE_CUBE_MAP, texture[0][world->blockType[i1 * 16 * 16 + i2][ch]]);
							glDrawArrays(GL_TRIANGLES, 0, 36);
							glBindVertexArray(0);
						}
						//}
					}
				}
			}
		}
		if (player->slots[player->currslot].id)
		{
			if (player->slots[player->currslot].id<STARTNOTBLOCKS)
				inhandShader.draw(player, texture[0], world);
			else if (player->slots[player->currslot].id < STARTINSTRUMENTS)
			{

			}
			else
			{
				Models[player->slots[player->currslot].id - STARTINSTRUMENTS]->draw(player, world);
			}
		}

		mininvShader.draw(player);

		skyShader.draw(player);
		if (control->showInv)
		{
			invShader.draw();
			invShader.drawInv(mininvShader.textureinv, mininvShader.texturenum, player);
			if (player->buf.id)
				onCursorShader.draw(control->lastX / control->width * 2 - 1, 1 - control->lastY / control->height * 2, mininvShader.textureinv[player->buf.id], mininvShader.texturenum, player->buf.num);
		}
		else
		{
			if (control->showBench)
			{
				workBenchShader.draw();
				workBenchShader.drawInv(mininvShader.textureinv, mininvShader.texturenum, player);
				if (player->buf.id)
					onCursorShader.draw(control->lastX / control->width * 2 - 1, 1 - control->lastY / control->height * 2, mininvShader.textureinv[player->buf.id], mininvShader.texturenum, player->buf.num);

			}
			else
			{
				if (control->showFurnace)
				{
					furnaceShader.draw(mininvShader.textureinv, mininvShader.texturenum, player, control->clickedFurnace);
					if (player->buf.id)
						onCursorShader.draw(control->lastX / control->width * 2 - 1, 1 - control->lastY / control->height * 2, mininvShader.textureinv[player->buf.id], mininvShader.texturenum, player->buf.num);
				}
				else
					cursorShader.draw();
			}
		}

		HPBarShader.draw(mininvShader.texturenum, player);

		for each (NetPlayer *netPlayer in world->PlayersVec)
		{
			if (netPlayer->going || netPlayer->movingLeg <= 2 * PI)
			{
				if (!netPlayer->going && netPlayer->movingLeg + 4.0f * world->deltaTime > PI && netPlayer->movingLeg < PI)
					netPlayer->movingLeg = 3 * PI;
				else
					netPlayer->movingLeg += 4.0f * world->deltaTime;
			}
			if (netPlayer->movingLeg > 2 * PI && netPlayer->going)
				netPlayer->movingLeg -= 2 * PI;
			drawPlayer->Draw(netPlayer, player);
			Models[0]->drawInNetPlayer(player, netPlayer, world);
		}
		tmp->looking = player->front;
		tmp->lookingbody = glm::normalize(glm::vec3(tmp->looking.x, 0.0f, tmp->looking.z));
		tmp->movingLeg += 4.0f * world->deltaTime;

		//drawPlayer->Draw(tmp, player);

		for each (Furnace *furnace in world->furnaceVec)
		{
			furnace->processMelt(world->deltaTime);
		}

		control->processBreaking();

		if (resConnect != -1)
		{
			socketUDP->sendCoords(player->position, player->front, (player->settingBlock < 0.2f), player->slots[player->currslot].id);
		}
		player->health += world->deltaTime / 2;
		if (player->health > 100.0f)
			player->health = 100.0f;
		if (player->health < 1)
		{
			printf_s("YOU DIED!!!\n");
			break;
		}
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	if (resConnect != -1)
	{
		socketUDP->~SocketUDP();
		endThreads = true;
		Threads::FinishRecieve();
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &skyShader.VAO);
	glDeleteBuffers(1, &skyShader.VBO);


	glfwTerminate();
	return 0;
}
