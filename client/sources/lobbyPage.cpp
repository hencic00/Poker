#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QtCore>
#include <QObject>

#include <iostream>
#include <thread>

#include "lobbyPage.h"
#include "lobbiesPage.h"
#include "playPage.h"
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
	thread = new QThread();
	Task *task = new Task(server, usersList, readyButton, this);
	task->stack = stack;
	task->moveToThread(thread);

	QFont font;
	font.setPixelSize(40);

	active = true;
	
	
	leaveButton->setEnabled(true);

	if (reponseUsers.size() > 1)
	{
		readyButton->setEnabled(true);
	}
	else 
	{
		readyButton->setEnabled(false);
	}

	for (int i = 0; i < reponseUsers.size(); ++i)
	{
		QJsonObject user = reponseUsers.at(i).toObject();

		myListItem *item = new myListItem();
		item->setFont(font);
		item->userSid = mySid;

		if (myUsername == user["username"].toString())
		{
			item->setText(user["username"].toString() + " (You)");
			mySid = user["userSid"].toInt();
		}
		else
		{
			item->setText(user["username"].toString());
		}
		item->userSid = user["userSid"].toInt();
		
		usersList->insertItem(0, item);
	}

	title->setText("Players in lobby \"" + lobbyName + "\":");

	connect(thread, SIGNAL (started()), task, SLOT (doWork()));
	thread->start();
}


void lobbyPage::initUI()
{
	QFont font;
	font.setPixelSize(40);

	usersList = new QListWidget(this);
	usersList->setSelectionMode( QAbstractItemView::SingleSelection );

	QFont font1;
	font1.setPixelSize(70);
	title = new QLabel("Players in lobby \"" + lobbyName + "\":");
	title->setStyleSheet("margin-bottom: 30px");
	
	title->setFont(font1);
	title->setAlignment(Qt::AlignCenter);
	title->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	QHBoxLayout *hbox = new QHBoxLayout();

	leaveButton = new QPushButton("  Leave lobby  ");
	leaveButton->setFont(font);
	leaveButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	leaveButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(leaveButton, &QPushButton::clicked, this, &lobbyPage::leavLobbyButtonPressed);


	readyButton = new QPushButton("  Ready  ");
	readyButton->setFont(font);
	readyButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	readyButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(readyButton, &QPushButton::clicked, this, &lobbyPage::readyButtonPressed);


	hbox->addWidget(leaveButton);
	hbox->addWidget(readyButton);

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(title, 0);
	vbox->addWidget(usersList, 5);
	vbox->addLayout(hbox, 1);


	this->setLayout(vbox);
}

void lobbyPage::leavLobbyButtonPressed()
{
	leaveLobby();
}

void lobbyPage::readyButtonPressed()
{
	readyButton->setEnabled(false);
	leaveButton->setEnabled(false);

	for (int i = 0; i < usersList->count(); ++i)
	{
		if (mySid == ((myListItem*)usersList->item(i))->userSid)
		{
			usersList->item(i)->setForeground(Qt::green);
			usersList->item(i)->setText(usersList->item(i)->text() + "✔");
			// this->repaint();
		}
	}

	server->sendReadyMessage();
}

void lobbyPage::startGame(int nmOfPlayers, QString* usernames, int* userSid)
{
	stack->setCurrentIndex(4);
	((playPage*)stack->widget(4))->draw(nmOfPlayers, usernames, userSid, mySid);
	((playPage*)stack->widget(4))->stackFocus();
	active = false;
	// thread->wait();
}

void lobbyPage::leaveLobby()
{
	server->sendLeaveLobbyMessage();
	// thread->wait();
	active = false;
}

void lobbyPage::focusOutEvent(QFocusEvent *event)
{
	std::cout << "nekaj" << std::endl;
}