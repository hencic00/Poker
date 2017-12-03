#ifndef SERVERHANDLER
#define SERVERHANDLER

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


class connectionHandler
{
    private:
		struct sockaddr_in address;
		int sock;
		struct sockaddr_in serv_addr;

		char* injectedTemplate;

		void woodoo();
		char* genRequest(char* templatePath, const char** params, int paramsC);

    public:
        connectionHandler();
        QJsonObject signUp(QString userName, QString email, QString password);
        QJsonObject login(QString email, QString password);
        QJsonObject logout(QString userId);
        QJsonObject getLobbies(QString userId);
        QJsonObject createLobby(QString userId);
};

#endif