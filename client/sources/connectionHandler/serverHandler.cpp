#include "connectionHandler/serverHandler.h"

#include <iostream>

serverHandler::serverHandler()
{
}

void serverHandler::createSocket()
{
	sock = 0;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
	}
  

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
	}
}


void serverHandler::sendCreateLobbyMessage(QString userId, QString name)
{
	QString request = "{\"agenda\":\"createLobby\", \"userId\":\"" + userId + "\", \"lobbyName\":\"" + name + "\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendGetLobbiesMessage(QString userId)
{
	QString request = "{\"agenda\":\"getLobbies\", \"userId\":\"" + userId + "\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendJoinLobbyMessage(QString userId, QString lobbyId)
{
	QString request = "{\"agenda\":\"joinLobby\", \"userId\":\"" + userId + "\", \"lobbyId\":\"" + lobbyId + "\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendLeaveLobbyMessage()
{
	QString request = "{\"agenda\":\"leaveLobby\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendReadyMessage()
{
	QString request = "{\"agenda\":\"ready\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendFoldMessage()
{
	QString request = "{\"agenda\":\"fold\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendRaiseMessage(int ammount)
{
	QString request = "{\"agenda\":\"raise\", \"data\": \"" + QString::number(ammount) + "\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

void serverHandler::sendCheckMessage()
{
	QString request = "{\"agenda\":\"check\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );
}

QJsonObject serverHandler::receviceMessage()
{
	int responseLength = 0;
	int responseLength1 = 0;


	recv(sock, (char*) &responseLength, 4, 0);
	responseLength1 |= ((responseLength >> 3 * 8) & 0x000000ff);
	responseLength1 |= ((responseLength >> 1 * 8) & 0x0000ff00);
	responseLength1 |= ((responseLength << 1 * 8) & 0x00ff0000);
	responseLength1 |= ((responseLength << 3 * 8) & 0xff000000);

	char* responseMsg = (char*) calloc(responseLength1 + 1, 1);


	recv(sock, responseMsg, responseLength1, 0);

	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(responseMsg, &err);
	QJsonObject obj = doc.object();

	return obj;
}
