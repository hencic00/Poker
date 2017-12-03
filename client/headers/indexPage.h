#pragma once

#include <QFrame>
#include <QLabel>
#include <QStackedWidget>
#include <QTimer>

#include "userData.h"
#include "connectionHandler/connectionHandler.h"


class indexPage : public QFrame
{
	Q_OBJECT  

	public:
		indexPage(QWidget *parent = 0);
		~indexPage();

		struct userData* user;
		char* userName;
		char* userId;
		char* email;

		QTimer* timer;
		QStackedWidget* stack;
		connectionHandler* server;
		QLabel *welcomeBanner;

	private:
		void initUI();
		void paintEvent(QPaintEvent *e);
		

	public slots:
		void timeOut();
		void logoutButtonPressed();
		void joinLobbyButtonClicked();

};