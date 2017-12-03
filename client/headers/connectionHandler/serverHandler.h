#ifndef SERVERHANDLER_H_
#define SERVERHANDLER_H_

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#define PORT 9999


class serverHandler
{
	private:
		struct sockaddr_in address;
		int sock;
		struct sockaddr_in serv_addr;

	public:
		serverHandler();
		void createSocket();
		void sendGetLobbiesMessage(QString userId);
		void sendCreateLobbyMessage(QString userId, QString name);
		void sendJoinLobbyMessage(QString userId, QString lobbyId);



		QJsonObject receviceMessage();

};

#endif