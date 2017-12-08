#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QListWidget>

#include "connectionHandler/serverHandler.h"


class Task : public QObject
{
	Q_OBJECT

	public:
		Task(serverHandler* s, QListWidget *uL);
		~Task();

		serverHandler* server;
		QListWidget *usersList;

	public slots:
		void doWork();
	signals:
		void workFinished();
};

#endif