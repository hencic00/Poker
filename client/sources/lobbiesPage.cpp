#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRect>
#include <QSvgWidget>
#include <QJsonObject>
#include <QJsonValue>
#include <QLineEdit>
#include <QJsonArray>

#include <iostream>

#include "lobbiesPage.h"
#include "lobbyPage.h"


lobbiesPage::lobbiesPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

lobbiesPage::~lobbiesPage()
{}

void lobbiesPage::initUI()
{

	QRect rec = QApplication::desktop()->screenGeometry();

	QFont font;
	font.setPixelSize(40);

	QHBoxLayout *hbox = new QHBoxLayout();
	QHBoxLayout *hbox1 = new QHBoxLayout();

	QPushButton* joinButton = new QPushButton("  Join lobby  ");
	joinButton->setFont(font);
	joinButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	joinButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(joinButton, &QPushButton::clicked, this, &lobbiesPage::joinButtonClicked);


	QPushButton* refresehButton = new QPushButton("  Refresh  ");
	refresehButton->setFont(font);
	refresehButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	refresehButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(refresehButton, &QPushButton::clicked, this, &lobbiesPage::refresehButtonClicked);


	hbox->addWidget(joinButton);
	hbox->addWidget(refresehButton);

	lobbyName = new QLineEdit();
	lobbyName->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	lobbyName->setStyleSheet("margin-top: 20px; padding: 50px;");
	lobbyName->setFont(font);
	lobbyName->setPlaceholderText("Lobby Name");

	QPushButton* createButton = new QPushButton("  Create lobby  ");
	createButton->setFont(font);
	connect(createButton, &QPushButton::clicked, this, &lobbiesPage::createButtonClicked);
	createButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	createButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);
	

	lobbiesList = new QListWidget(this);
	lobbiesList->setSelectionMode( QAbstractItemView::SingleSelection );

	hbox1->addWidget(lobbyName);
	hbox1->addWidget(createButton);


	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(lobbiesList, 5);
	vbox->addLayout(hbox, 1);
	vbox->addLayout(hbox1, 1);
	this->setLayout(vbox);
}

void lobbiesPage::stackFocus()
{
	refreshLobies();
}

void lobbiesPage::refreshLobies()
{
	server1->createSocket();
	server1->sendGetLobbiesMessage(userId);
	QJsonObject response = server1->receviceMessage();

	QJsonValue data = response.value("data");
    QJsonArray lobbArray = data.toArray();

    lobbiesList->clear();

    foreach (const QJsonValue & lobby, lobbArray)
    {
		QJsonObject obj = lobby.toObject();

		QFont font;
		font.setPixelSize(40);
		myListItem1 *item = new myListItem1();
		item->setText(obj["name"].toString());
		item->lobbyId = obj["id"].toString();
		item->setFont(font);

		lobbiesList->insertItem(0, item);
	}
}

void lobbiesPage::refresehButtonClicked()
{
	refreshLobies();
}

void lobbiesPage::createButtonClicked()
{
	QString name = lobbyName->text();
	std::cout << name.toStdString() << std::endl;


	if (name != "")
	{
		server1->createSocket();
		server1->sendCreateLobbyMessage(userId, name);
		QJsonObject response = server1->receviceMessage();
		QJsonObject data = response.value("data").toObject();
		QJsonValue users = data.value("users");
		QJsonArray usersArray = users.toArray();

		QJsonObject user = usersArray.at(0).toObject();


		stack->setCurrentIndex(6);
		((lobbyPage*)stack->widget(6))->myUsername = QString::fromStdString(std::string(userName));
		((lobbyPage*)stack->widget(6))->lobbyName = data.value("name").toString();
		((lobbyPage*)stack->widget(6))->reponseUsers = usersArray;
		((lobbyPage*)stack->widget(6))->stackFocus();
	}
}

void lobbiesPage::joinButtonClicked()
{
	server1->createSocket();
	server1->sendJoinLobbyMessage(userId, ((myListItem1*) (lobbiesList->selectedItems()[0]))->lobbyId);
	QJsonObject response = server1->receviceMessage();
	QJsonObject data = response.value("data").toObject();
	QJsonValue users = data.value("users");
	QJsonArray usersArray = users.toArray();


	stack->setCurrentIndex(6);
	((lobbyPage*)stack->widget(6))->myUsername = QString::fromStdString(std::string(userName));
	((lobbyPage*)stack->widget(6))->lobbyName = data.value("name").toString();
	((lobbyPage*)stack->widget(6))->reponseUsers = usersArray;
	((lobbyPage*)stack->widget(6))->stackFocus();
}
