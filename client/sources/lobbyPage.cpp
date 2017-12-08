#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QThread>
#include <QtCore>
#include <QObject>

#include <iostream>
#include <thread>

#include "lobbyPage.h"
#include "task.h"


lobbyPage::lobbyPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

lobbyPage::~lobbyPage()
{}

void serverCommThread()
{

	//std::cout << "nekaj" << std::endl;
	//QJsonObject response = server->receviceMessage();



	// QJsonValue data = response.value("data");
	// QJsonValue users = response.value("users");
 //    QJsonArray usersArray = users.toArray();

 //    foreach (const QJsonValue & user, usersArray)
 //    {
	// 	QJsonObject obj = user.toObject();

	// 	QFont font;
	// 	font.setPixelSize(40);
	// 	QListWidgetItem *item = new QListWidgetItem();
	// 	item->setText(obj["username"].toString());
	// 	item->setFont(font);

	// 	usersList->insertItem(0, item);
	// }
}



void lobbyPage::stackFocus()
{
	QThread *thread = new QThread();
	Task *task = new Task(server, usersList);
	task->moveToThread(thread);

	QFont font;
	font.setPixelSize(40);
	myListItem *item = new myListItem();
	item->setText(myUsername + " (You)");
	item->setFont(font);
	item->userSid = mySid;

	title->setText("Players in lobby \"" + lobbyName + "\":");

	usersList->insertItem(0, item);


	connect( thread, &QThread::started, task, &Task::doWork );
	connect( task, &Task::workFinished, thread, &QThread::quit );
	thread->start();
}


void lobbyPage::initUI()
{
	usersList = new QListWidget(this);
	usersList->setSelectionMode( QAbstractItemView::SingleSelection );

	QFont font1;
	font1.setPixelSize(70);
	title = new QLabel("Players in lobby \"" + lobbyName + "\":");
	title->setStyleSheet("margin-bottom: 30px");
	
	title->setFont(font1);
	title->setAlignment(Qt::AlignCenter);
	title->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(title, 0);
	vbox->addWidget(usersList, 5);


	this->setLayout(vbox);
}