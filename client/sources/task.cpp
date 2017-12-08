#define _BSD_SOURCE

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <iostream>

#include "task.h"

Task::Task(serverHandler* s, QListWidget *uL):QObject()
{
	server = s;
	usersList = uL;			 
}

Task::~Task()
{}

void Task::doWork()
{
	QFont font;
	font.setPixelSize(40);


	QJsonObject response = server->receviceMessage();

	
	// QJsonValue users = response.value("users");
	// QJsonArray usersArray = users.toArray();

	if (response.value("agenda").toString() == "playerJoined")
	{
		QJsonObject data = response.value("data").toObject();
		QListWidgetItem *item = new QListWidgetItem();
		item->setText(data["username"].toString());
		item->setFont(font);

		usersList->insertItem(0, item);
	}


	// foreach (const QJsonValue & user, usersArray)
	// {
	// 	QJsonObject obj = user.toObject();

	// 	QFont font;
	// 	font.setPixelSize(40);
	// 	QListWidgetItem *item = new QListWidgetItem();
	// 	item->setText(obj["username"].toString());
	// 	item->setFont(font);

	// 	usersList->insertItem(0, item);
	// }
}