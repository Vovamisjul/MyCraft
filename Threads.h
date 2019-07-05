#pragma once
#include "World.h"
#include "WinSock2.h"
#include "SocketTCP.h"
#include "SocketUDP.h"
#include "Player.h"
#include <thread>

static class Threads {
public:
	static void StartRecieve(World *world, Player *player, SOCKET sockTCP, SOCKET sockUDP, bool *endRecieve);
	static void FinishRecieve();
private:
	static std::thread threadTCP, threadUDP;
	static void RecieveCoordsTCP(World *world, Player *player, SOCKET sock, bool *endRecieve);
	static void RecieveCoordsUDP(World *world, SOCKET sock, bool *endRecieve);
	static void DefineCoords(char *mess, int *block, int *chunk, int *type);
	static void DefineDamage(char *mess, int *damage);
};