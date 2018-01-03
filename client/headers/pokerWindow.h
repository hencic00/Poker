#pragma once

#include <QFrame>
#include <QStyle>
#include <QStackedWidget>
#include <QTimer>
#include <QCloseEvent>

#include <string>

#include "connectionHandler/connectionHandler.h"
#include "connectionHandler/serverHandler.h"
#include "userData.h"

#include "lobbyPage.h"

class pokerWindow : public QFrame
{
	Q_OBJECT  

	public:
		pokerWindow(QWidget *parent = 0);
		~pokerWindow();

	private:
		void initUI();
		void setWindowGeometry();
		void closeEvent(QCloseEvent *event);

		QStackedWidget* stack;
		QTimer *timer;
		lobbyPage* lobby;

		connectionHandler* server;
		serverHandler* server1;
		char userName[100];
		char userId[100];
		char email[100];

	public slots:
		void navigationRequestReceived(char* title, int index);
		void nekaj();
};