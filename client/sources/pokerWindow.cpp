#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

#include <iostream>
#include <map>

#include "pokerWindow.h"
#include "loginPage.h"
#include "signUpPage.h"
#include "loadingPage.h"
#include "lobbiesPage.h"
#include "playPage.h"
#include "indexPage.h"
#include "lobbyPage.h"

pokerWindow::pokerWindow(QWidget *parent):QFrame(parent)
{			 
	server = new connectionHandler();
	server1 = new serverHandler();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(nekaj()));

	email[0] = '\0';
	userName[0] = '\0';
	userId[0] = '\0';

	initUI();
}


pokerWindow::~pokerWindow()
{}

void pokerWindow::initUI()
{	
	stack = new QStackedWidget();

	loginPage* login = new loginPage();
	login->server = server;
	login->userName = userName;
	login->email = email;
	login->userId = userId;
	login->stack = stack;
	connect(login, &loginPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	signUpPage* signUp = new signUpPage();
	signUp->server = server;
	signUp->userName = userName;
	signUp->email = email;
	signUp->userId = userId;
	connect(signUp, &signUpPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	loadingPage* loading = new loadingPage();
	connect(loading, &loadingPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	lobbiesPage* lobbies = new lobbiesPage();
	lobbies->server = server;
	lobbies->userId = userId;
	lobbies->server1 = server1;
	lobbies->stack = stack;
	connect(lobbies, &lobbiesPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	playPage* play = new playPage();

	indexPage* index = new indexPage();
	index->userName = userName;
	index->email = email;
	index->userId = userId;
	index->server = server;
	index->stack = stack;

	lobbyPage* lobby = new lobbyPage();
	lobby->server = server1;

	
	stack->addWidget(login);
	stack->addWidget(signUp);
	stack->addWidget(loading);
	stack->addWidget(lobbies);
	stack->addWidget(play);
	stack->addWidget(index);
	stack->addWidget(lobby);



	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(stack);

	

	setWindowGeometry();
	this->setLayout(vbox);
	this->setWindowTitle("Login");

}

void pokerWindow::setWindowGeometry()
{
	QRect rec = QApplication::desktop()->screenGeometry();
	resize(rec.width() * 0.8, rec.height() * 0.8);
	move(rec.width() * 0.1, rec.height() * 0.07);
}

void pokerWindow::navigationRequestReceived(char* title, int index)
{
	if (index == 2)
	{
		timer->start(500);
	}

	stack->setCurrentIndex(index);
	setWindowTitle(title);
}

void pokerWindow::nekaj()
{
	stack->setCurrentIndex(5);
	timer->stop();
}

void pokerWindow::closeEvent(QCloseEvent *event)
{
	if (email[0] != '\0' && userName[0] != '\0' && userId[0] != '\0')
	{
		QJsonObject object = server->logout(QString(userId));
		QJsonValue val = object.value("status");

		if (val.toString() == "ok")
		{
			stack->setCurrentIndex(2);
			timer->start(500);

			email[0] = '\0';
			userName[0] = '\0';
			userId[0] = '\0';
		}
	}
}