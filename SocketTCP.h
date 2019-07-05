#pragma once
#include "stdio.h"
#include "winsock2.h"
#include "Ws2tcpip.h"
#include "string.h"
#include <thread>
#include <glm/glm.hpp>
#define SENDEDCOORDSSET 1
#define SENDEDCOORDSGET 2
#define FIRSTCOORDS 3
#define ENDFIRSTCOORDS 4
#define DAMAGE 10
#define REQCHUNKS 11
#define ANOTHERBLOCK 12
#define NEWCHUNK 13

class SocketTCP {
public:
	SOCKET sock;
	SocketTCP(char *ip, int port);
	void sendCoords(int coords, int chunk, int blocktype, bool set);
	void sendHit(int id, int damage);
	void sendReqToNewChunk(int numChunk);
private:
	WSADATA lpdata;
};