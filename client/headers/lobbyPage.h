#pragma once

#include <QFrame>
#include <QListWidget>
#include <QJsonArray>
#include <QLabel>

#include "connectionHandler/serverHandler.h"

#ifndef MYLISTITEM
#define MYLISTITEM
class myListItem : public QListWidgetItem
{
	public:
		QString userSid;
};
#endif

class lobbyPage : public QFrame
{
	Q_OBJECT  

	public:
		lobbyPage(QWidget *parent = 0);
		void stackFocus();
		~lobbyPage();

		serverHandler* server;
		QListWidget *usersList;
		QLabel* title;

		int mySid;
		QString myUsername;
		QString lobbyName;
		QJsonArray userList;
		char* userId;

	private:
		void initUI();
};
