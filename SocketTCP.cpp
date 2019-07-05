#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "SocketTCP.h"

SocketTCP::SocketTCP(char *ip, int port)
{
	if (WSAStartup(0x0202, &lpdata) == 0)
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock != INVALID_SOCKET)
		{
			struct sockaddr_in ssa, csa;
			struct sockaddr *sp, *cp;
			sp = (struct sockaddr *)&ssa;
			cp = (struct sockaddr *)&csa;
			ssa.sin_family = AF_INET;
			ssa.sin_addr.s_addr = inet_addr(ip);
			if (ssa.sin_addr.s_addr == -1)
			{
				printf_s("error ip");
				return;
			}
			ssa.sin_port = htons(port);
			if (connect(sock, sp, sizeof(ssa)) == SOCKET_ERROR)
				printf_s("error port");

		}
		else
		{
			printf_s("Failed to create socket");
		}
	}
}

void SocketTCP::sendCoords(int coords, int chunk, int blocktype, bool set)
{
	char msg[2 + 3 * sizeof(int)];
	msg[0] = ANOTHERBLOCK;
	if (set)
		msg[1] = SENDEDCOORDSSET;
	else
		msg[1] = SENDEDCOORDSGET;
	char *coord;
	char *type;
	type = (char *)(&blocktype);
	coord = (char *)(&coords);
	for (int i = 0; i < sizeof(int); i++)
	{
		msg[2 + i] = coord[i];
	}
	coord = (char *)(&chunk);
	for (int i = 0; i < sizeof(int); i++)
	{
		msg[2 + sizeof(int) + i] = coord[i];
	}
	for (int i = 0; i < sizeof(int); i++)
	{
		msg[2 + 2 * sizeof(int) + i] = type[i];
	}
	send(sock, msg, 2 + 3 * sizeof(int), 0);
}

void SocketTCP::sendReqToNewChunk(int numChunk)
{
	char msg[1 + sizeof(int)];
	msg[0] = REQCHUNKS;
	char *chunk = (char *)(&numChunk);
	for (int i = 0; i < sizeof(int); i++)
	{
		msg[1 + i] = chunk[i];
	}
	send(sock, msg, 1 + sizeof(int), 0);

}

void SocketTCP::sendHit(int id, int damage)
{
	char msg[1 + 2 * sizeof(int)];
	msg[0] = DAMAGE;
	char *Id;
	char *Damage;
	Id = (char *)(&id);
	Damage = (char *)(&damage);
	for (int i = 0; i < sizeof(int); i++)
	{
		msg[1 + i] = Id[i];
	}
	for (int i = 0; i < sizeof(int); i++)
	{
		msg[1 + sizeof(int) + i] = Damage[i];
	}
	send(sock, msg, 1 + 2 * sizeof(int), 0);
}