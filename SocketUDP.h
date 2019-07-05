#pragma once
#include "stdio.h"
#include "winsock2.h"
#include "Ws2tcpip.h"
#include "string.h"
#include <thread>
#include <glm/glm.hpp>
#include "World.h"

#define CONNECT 7
#define DISCONNECT 8
#define COORDS 9

class SocketUDP {
public:
	SOCKET sock;
	SocketUDP(char *ip, int port);
	~SocketUDP();
	void sendCoords(glm::vec3 coords, glm::vec3 looking, bool hitting, char type);
	void sendHit(int id, int damage);
	void recieveCoords(World *world);
private:
	WSADATA lpdata;
	struct sockaddr_in ssa;
	struct sockaddr *sp;
};