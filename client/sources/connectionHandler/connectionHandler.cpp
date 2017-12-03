#include "connectionHandler/connectionHandler.h"

#include <iostream>

connectionHandler::connectionHandler()
{
	injectedTemplate = NULL;
}

char* connectionHandler::genRequest(char* templatePath, const char** params, int paramsC)
{	
	if (injectedTemplate)
	{
		free(injectedTemplate);
	}


	FILE *templateFp = fopen(templatePath, "r");
	
	int templazeFileSize;
	fseek(templateFp, 0, SEEK_END);
	templazeFileSize = ftell(templateFp);
	fseek(templateFp, 0, SEEK_SET);

	char* templateFileData = (char* )calloc(templazeFileSize + 1, sizeof(char));
	fread(templateFileData, templazeFileSize, 1, templateFp);

	int injectTemplateLength = templazeFileSize - paramsC * 2;

	for (int i = 0; i < paramsC; ++i)
	{
		injectTemplateLength += strlen(params[i]);
	}

	injectedTemplate = (char* )calloc(injectTemplateLength + 1, sizeof(char));

	// Dont judge
	if (paramsC == 0)
	{ memcpy(injectedTemplate, templateFileData, injectTemplateLength + 1); }
	else if (paramsC == 1)
	{ sprintf(injectedTemplate, templateFileData, params[0]); }
	else if(paramsC == 2)
	{ sprintf(injectedTemplate, templateFileData, params[0], params[1]); }
	else if(paramsC == 3)
	{ sprintf(injectedTemplate, templateFileData, params[0], params[1], params[2]); }
	// -----------------------------------------------------

	free(templateFileData);

	fclose(templateFp);

	return injectedTemplate;

}

void connectionHandler::woodoo()
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

QJsonObject connectionHandler::signUp(QString userName, QString email, QString password)
{
	QString hello = "{\"username\": \"" + userName + "\", \"password\": \"" + password + "\", \"email\": \"" + email + "\", \"agenda\": \"register\"}";
	int length = hello.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	woodoo();

	const char *contentArs[2];
	contentArs[0] = email.toStdString().c_str();
	std::cout << email.toStdString().c_str() << std::endl;
	contentArs[1] = password.toStdString().c_str();

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , hello.toStdString().c_str(), length , 0 );

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

QJsonObject connectionHandler::login(QString email, QString password)
{
	QString request = "{\"agenda\":\"login\", \"email\":\"" + email + "\", \"password\":\"" + password + "\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	woodoo();

	const char *contentArs[2];
	contentArs[0] = email.toStdString().c_str();
	std::cout << email.toStdString().c_str() << std::endl;
	contentArs[1] = password.toStdString().c_str();

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );

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

QJsonObject connectionHandler::logout(QString userId)
{
	QString request = "{\"agenda\":\"logout\", \"userId\":\"" + userId + "\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	woodoo();

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );

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

QJsonObject connectionHandler::getLobbies(QString userId)
{
	QString request = "{\"agenda\":\"getLobbies\", \"userId\":\"" + userId + "\"}";
	std::cout << request.toStdString() << std::endl;

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	woodoo();

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );

	int responseLength = 0;
	int responseLength1 = 0;


	recv(sock, (char*) &responseLength, 4, 0);
	responseLength1 |= ((responseLength >> 3 * 8) & 0x000000ff);
	responseLength1 |= ((responseLength >> 1 * 8) & 0x0000ff00);
	responseLength1 |= ((responseLength << 1 * 8) & 0x00ff0000);
	responseLength1 |= ((responseLength << 3 * 8) & 0xff000000);

	char* responseMsg = (char*) calloc(responseLength1 + 1, 1);


	recv(sock, responseMsg, responseLength1, 0);

	std::cout << responseMsg << std::endl;

	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(responseMsg, &err);
	QJsonObject obj = doc.object();

	return obj;
}

QJsonObject connectionHandler::createLobby(QString userId)
{
	QString request = "{\"agenda\":\"createLobby\", \"userId\":\"" + userId + "\", \"lobbyName\":\"test\"}";

	int length = request.length();
	int length1 = 0;

	length1 |= ((length >> 3 * 8) & 0x000000ff);
	length1 |= ((length >> 1 * 8) & 0x0000ff00);
	length1 |= ((length << 1 * 8) & 0x00ff0000);
	length1 |= ((length << 3 * 8) & 0xff000000);

	woodoo();

	send(sock , (char*) &length1 , 4 , 0 );
	send(sock , request.toStdString().c_str(), length , 0 );

	int responseLength = 0;
	int responseLength1 = 0;


	recv(sock, (char*) &responseLength, 4, 0);
	responseLength1 |= ((responseLength >> 3 * 8) & 0x000000ff);
	responseLength1 |= ((responseLength >> 1 * 8) & 0x0000ff00);
	responseLength1 |= ((responseLength << 1 * 8) & 0x00ff0000);
	responseLength1 |= ((responseLength << 3 * 8) & 0xff000000);

	char* responseMsg = (char*) calloc(responseLength1 + 1, 1);


	recv(sock, responseMsg, responseLength1, 0);

	std::cout << responseMsg << std::endl;

	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(responseMsg, &err);
	QJsonObject obj = doc.object();

	return obj;
}