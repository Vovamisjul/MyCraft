#pragma once
#include "Player.h"
#include "World.h"
#include "inventory.h"
#include "SocketTCP.h"
#include "SocketUDP.h"
#include <glfw3.h>

#define BYWOODENAXE 4
#define BYWOODENPICKAXE 9

class Control {
public:
	bool showInv;
	bool showBench;
	bool showFurnace;
	bool breakeBlock;

	int breakedBlock;
	int breakedChunk;
	Player *player;
	World *world;
	GLfloat lastX = 400, lastY = 300;
	int width, height;
	Furnace *clickedFurnace;
	SocketTCP *socket;
	SocketUDP *socketUdp;

	Control(Player *player, World *world);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void startBreaking();

	void processBreaking();

	int getTextureBroken();
private:
	bool firstMouse = true;
	bool clickedLeft;
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;

	glm::vec3 breakingBlock;
	float breakingTime;
	const float playerWidth = 0.2f;

	glm::vec3 clickedCoords;
	bool locationAllPlayersInBlock(float x, float y, float z);
	int locationOtherPlayerInBlock(float x, float y, float z);
	void tryHitPlayer();
	const int* blocksBreakedByInstrument[NUMINSTRUMENTS];
	const int numBreakable[NUMINSTRUMENTS] = {0, BYWOODENAXE, BYWOODENPICKAXE};
	const int blocksBreakedByWoodenAxe[BYWOODENAXE] = {blocktype::LEAVE, blocktype::LOG, blocktype::WBENCH, blocktype::PLANK};
	const int blocksBreakedByWoodenPickaxe[BYWOODENPICKAXE] = {
		blocktype::CACTUS, blocktype::CLAY, blocktype::DIRT, blocktype::GLASS, blocktype::GRASS, 
		blocktype::MELON, blocktype::SAND, blocktype::STONE, blocktype::FURNACE};
	const float multiplyerByInstrument[NUMINSTRUMENTS] = { 1, 1, 1 };
	const int damageByInstruments[NUMINSTRUMENTS] = {10, 7, 5};
	/*
	const int blocksBreakedByWoodenPickaxe[NUMBLOCKS - BYAXE - 1 + 1] = {
		blocktype::BACKEDCLAY, blocktype::BRICKS, blocktype::CACTUS, blocktype::CLAY, blocktype::COALORE, 
		blocktype::COPPERORE, blocktype::DIAMONDORE, blocktype::DIRT, blocktype::EMERALDORE, blocktype::FURNACE, 
		blocktype::GLASS, blocktype::GOLDORE, blocktype::GRASS, blocktype::IRONORE, blocktype::MELON, 
		blocktype::SAND, blocktype::STONE, blocktype::STONEBRICKS, NULL };*/
	void tryAddTime();
};