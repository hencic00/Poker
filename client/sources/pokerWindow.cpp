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

pokerWindow::pokerWindow(QWidget *parent):QFrame(parent)
{			 

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


	stack = new QStackedWidget();
	stack->addWidget(login);
	stack->addWidget(signUp);
	stack->addWidget(loading);



	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(stack);

	

	setWindowGeometry();
	this->setLayout(vbox);
	this->setWindowTitle("Login");

}

void pokerWindow::setWindowGeometry()
{
	QRect rec = QApplication::desktop()->screenGeometry();
	resize(rec.width() * 0.7, rec.height() * 0.7);
	move(rec.width() * 0.15, rec.height() * 0.12);
}

void pokerWindow::navigationRequestReceived(char* title, int index)
{
	stack->setCurrentIndex(index);
	setWindowTitle(title);
}