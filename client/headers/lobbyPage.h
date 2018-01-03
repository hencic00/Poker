#pragma once

#include <QFrame>
#include <QListWidget>
#include <QJsonArray>
#include <QLabel>
#include <QStackedWidget>
#include <QThread>
#include <QPushButton>

#include "connectionHandler/serverHandler.h"

#ifndef MYLISTITEM
#define MYLISTITEM
class myListItem : public QListWidgetItem
{
	public:
		int userSid;
};
#endif

class lobbyPage : public QFrame
{
	Q_OBJECT  

	public:
		lobbyPage(QWidget *parent = 0);
		void stackFocus();
		void focusOutEvent(QFocusEvent *event);
		void leaveLobby();
		void startGame(int nmOfPlayers, QString* usernames, int* userSid);
		~lobbyPage();

		serverHandler* server;
		QListWidget *usersList;
		QLabel* title;

		int mySid;
		QString myUsername;
		QString lobbyName;
		QJsonArray reponseUsers;
		char* userId;
		QStackedWidget* stack;
		bool active;
		QThread *thread;
		QPushButton* leaveButton;
		QPushButton* readyButton;

		void leavLobbyButtonPressed();
		void readyButtonPressed();

	private:
		void initUI();
};
