#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "SocketUDP.h"

SocketUDP::SocketUDP(char *ip, int port)
{
	if (WSAStartup(0x0202, &lpdata) == 0)
	{
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock != INVALID_SOCKET)
		{
			sp = (struct sockaddr *)&ssa;
			ssa.sin_family = AF_INET;
			ssa.sin_addr.s_addr = inet_addr(ip);
			ssa.sin_port = htons(port);
			/*char connectmess[1];
			connectmess[0] = CONNECT;
			sendto(sock, connectmess, 1, 0, sp, sizeof(ssa));*/
		}
		else printf_s("Failed to create socket");
	}
	else printf_s("Failed to start");
}

SocketUDP::~SocketUDP()
{
	char disconnectmess[1];
	disconnectmess[0] = DISCONNECT;
	sendto(sock, disconnectmess, 1, 0, sp, sizeof(ssa));
	closesocket(sock);
}

void SocketUDP::sendCoords(glm::vec3 coords, glm::vec3 looking, bool hitting, char type)
{
	//0 - "COORDS"
	//sizeof(glm::vec3) - coords
	//sizeof(glm::vec3) - looking
	//sizeof(bool) - is settingblock
	//sizeof(char) - type in hand
	char mess[1 + 2 * sizeof(glm::vec3) + sizeof(bool) + sizeof(char)];
	char *temp;
	temp = (char *)(&coords);
	mess[0] = COORDS;
	for (int i = 0; i < sizeof(glm::vec3); i++)
	{
		mess[1 + i] = temp[i];
	}

	temp = (char *)(&looking);
	for (int i = 0; i < sizeof(glm::vec3); i++)
	{
		mess[1 + sizeof(glm::vec3) + i] = temp[i];
	}

	temp = (char *)(&hitting);
	for (int i = 0; i < sizeof(bool); i++)
	{
		mess[1 + 2 * sizeof(glm::vec3) + i] = temp[i];
	}

	temp = (char *)(&type);
	for (int i = 0; i < sizeof(char); i++)
	{
		mess[1 + 2 * sizeof(glm::vec3) + sizeof(bool) + i] = temp[i];
	}
	sendto(sock, mess, 1 + 2 * sizeof(glm::vec3) + sizeof(bool) + sizeof(char), 0, sp, sizeof(ssa));
}

void SocketUDP::recieveCoords(World *world)
{
	char buf[2 + 2 * sizeof(glm::vec3) + sizeof(bool) + sizeof(char)];
	struct sockaddr_in ssa;
	int size = sizeof(ssa);
	int res = -1;
	while (1)
	{
		if (res > 0)
		{
			NetPlayer *player = new NetPlayer();
			player->id = buf[1];
			switch (buf[0])
			{
				/*case CONNECT:
				{
					player.ip = ssa.sin_addr.S_un.S_addr;
					player.port = ssa.sin_port;
					player.position = glm::vec3(0.0f);
					player.looking = glm::vec3(0.0f);
					break;
				}*/
			case COORDS:
			{
				player->position = *((glm::vec3 *)(buf + 2));
				player->looking = *((glm::vec3 *)(buf + 2 + sizeof(glm::vec3)));
				bool tempHitting = *((bool *)(buf + 2 + 2 * sizeof(glm::vec3)));
				if (!player->hitting && tempHitting)
					player->timeHitting = 0;
				player->hitting = tempHitting;
				player->blockType = *((char *)(buf + 2 + 2 * sizeof(glm::vec3) + sizeof(bool)));
				bool find = false;
				for each (NetPlayer *netPlayer in world->PlayersVec)
				{
					if (netPlayer->id == player->id)
					{
						netPlayer->position = player->position;
						netPlayer->looking = player->looking;
						find = true;
					}
				}
				if (!find)
				{
					world->PlayersVec.push_back(player);
				}
				break;
			}
			case DISCONNECT:
			{
				for (int i = 0; i < world->PlayersVec.size(); i++)
				{
					if (world->PlayersVec[i]->id == player->id)
					{
						world->PlayersVec.erase(world->PlayersVec.cbegin() + i);
						break;
					}
				}
				break;
			}
			}
			delete player;
		}
		res = recvfrom(sock, buf, 2 + 2 * sizeof(glm::vec3), 0, (struct sockaddr *)&ssa, &size);
	}
}

void SocketUDP::sendHit(int id, int damage)
{
	char msg[1 + 2 * sizeof(int)];
	msg[0] = 10; //DAMAGE
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
	sendto(sock, msg, 1 + 2 * sizeof(int), 0, sp, sizeof(ssa));
}