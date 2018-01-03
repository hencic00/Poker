#pragma once

#include <QFrame>
#include <QListWidget>
#include <QStackedWidget>
#include <QJsonArray>

#include "connectionHandler/connectionHandler.h"
#include "connectionHandler/serverHandler.h"

#ifndef MYLISTITEM1
#define MYLISTITEM1
class myListItem1 : public QListWidgetItem
{
	public:
		QString lobbyId;
};
#endif

class lobbiesPage : public QFrame
{
	Q_OBJECT  

	public:
		lobbiesPage(QWidget *parent = 0);
		void stackFocus();
		~lobbiesPage();

		char* title;
		int index;
		connectionHandler* server;
		serverHandler* server1;
		char* userId;
		char* userName;

		QListWidget *lobbiesList;
		QLineEdit* lobbyName;
		QStackedWidget* stack;

	private:
		void initUI();
		void refreshLobies();

	public slots:
		void refresehButtonClicked();
		void createButtonClicked();
		void joinButtonClicked();

	signals:
		void navigateTo(char* title, int index);
};