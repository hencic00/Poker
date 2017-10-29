#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRect>
#include <iostream>


#include "loginPage.h"

loginPage::loginPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

loginPage::~loginPage()
{}

void loginPage::initUI()
{	
	QRect rec = QApplication::desktop()->screenGeometry();

	QFont font;
	font.setPixelSize(40);


	QLineEdit* email = new QLineEdit();
	email->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	email->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	email->setFont(font);
	email->setPlaceholderText("E-mail");


	QLineEdit* password = new QLineEdit();
	password->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	password->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	password->setFont(font);
	password->setPlaceholderText("Password");

	QHBoxLayout *hbox = new QHBoxLayout();

	QPushButton* loginButton = new QPushButton("  Login  ");
	loginButton->setFont(font);
	loginButton->setIcon(QIcon("./images/key.svg"));
	loginButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	loginButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	loginButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(loginButton, &QPushButton::clicked, this, &loginPage::loginButtonClicked);

	QPushButton* signUpButton = new QPushButton("  Sign up  ");
	signUpButton->setFont(font);
	signUpButton->setIcon(QIcon("./images/contract.svg"));
	signUpButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	signUpButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	signUpButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(signUpButton, &QPushButton::clicked, this, &loginPage::signUpButtonClicked);

	hbox->addWidget(loginButton);
	hbox->addWidget(signUpButton);


	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setContentsMargins(rec.width()*0.22, rec.width()*0.12, rec.width()*0.22, rec.width()*0.12);
	vbox->setSpacing(0);
	// vbox->setMargin(1);

	vbox->addWidget(email);
	vbox->addWidget(password);
	vbox->addLayout(hbox);

	this->setLayout(vbox);
}

void loginPage::loginButtonClicked()
{
	emit navigateTo("Loading", 2);
}

void loginPage::signUpButtonClicked()
{
	emit navigateTo("Sign up", 1);
}