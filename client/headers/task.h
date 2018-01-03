#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "connectionHandler/serverHandler.h"
#include "playPage.h"
#include "lobbyPage.h"


class Task : public QObject
{
	Q_OBJECT

	public:
		Task(serverHandler* s, QListWidget *uL, QPushButton* rB, lobbyPage* papa);
		Task(serverHandler* s, playPage* papa);
		~Task();

		serverHandler* server;
		QListWidget *usersList;
		QStackedWidget* stack;
		QPushButton* readyButton;
		lobbyPage* foter;
		playPage* foter1;
		std::map<std::string, QString> card;

	public slots:
		void doWork();
		void doWork1();
	signals:
		void workFinished();
};

#endif