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
#include "lobbyPage.h"
#include "playPage.h"

pokerWindow::pokerWindow(QWidget *parent):QFrame(parent)
{			 

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(nekaj()));

	initUI();
}


pokerWindow::~pokerWindow()
{}

void pokerWindow::initUI()
{	
	loginPage* login = new loginPage();
	connect(login, &loginPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	signUpPage* signUp = new signUpPage();
	connect(signUp, &signUpPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	loadingPage* loading = new loadingPage();
	connect(loading, &loadingPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	lobbyPage* lobby = new lobbyPage();
	connect(lobby, &lobbyPage::navigateTo, this, &pokerWindow::navigationRequestReceived);

	playPage* play = new playPage();


	stack = new QStackedWidget();
	stack->addWidget(login);
	stack->addWidget(signUp);
	stack->addWidget(loading);
	stack->addWidget(lobby);
	stack->addWidget(play);



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
		std::cout << "nekaj1" << std::endl;
		timer->start(500);
	}

	stack->setCurrentIndex(index);
	setWindowTitle(title);
}

void pokerWindow::nekaj()
{
	stack->setCurrentIndex(3);
	timer->stop();
}