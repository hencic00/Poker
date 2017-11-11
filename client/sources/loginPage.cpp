#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRect>
#include <iostream>
#include <QSvgWidget>


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

	QHBoxLayout * hbox2  = new QHBoxLayout();
	QSvgWidget* banner = new QSvgWidget("./images/signUp.svg");
	banner->setFixedSize(rec.width() * 0.35, rec.height()*0.13);
	hbox2->addStretch(1);
	hbox2->addWidget(banner);
	hbox2->addStretch(1);


	QLineEdit* email = new QLineEdit();
	email->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	email->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	email->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	email->setFont(font);
	email->setPlaceholderText("E-mail");

	QLineEdit* password = new QLineEdit();
	password->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	password->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	password->setFont(font);
	password->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	password->setPlaceholderText("Password");


	QHBoxLayout *hbox = new QHBoxLayout();

	QPushButton* loginButton = new QPushButton("  Login  ");
	loginButton->setFont(font);
	loginButton->setIcon(QIcon("./images/key.svg"));
	loginButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	loginButton->setFixedSize(rec.width() * 0.125, rec.height()*0.09);
	loginButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	loginButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(loginButton, &QPushButton::clicked, this, &loginPage::loginButtonClicked);

	QPushButton* signUpButton = new QPushButton("  Sign up  ");
	signUpButton->setFont(font);
	signUpButton->setIcon(QIcon("./images/contract.svg"));
	signUpButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	signUpButton->setFixedSize(rec.width() * 0.125, rec.height()*0.09);
	signUpButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	connect(signUpButton, &QPushButton::clicked, this, &loginPage::signUpButtonClicked);

	hbox->addWidget(loginButton);
	hbox->addWidget(signUpButton);


	QHBoxLayout *hbox1 = new QHBoxLayout();

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setSpacing(0);

	
	vbox->addWidget(email);
	vbox->addWidget(password);
	vbox->addLayout(hbox);

	hbox1->addStretch(1);
	hbox1->addLayout(vbox);
	hbox1->addStretch(1);

	QVBoxLayout *vbox4 = new QVBoxLayout();
	vbox4->addStretch(6);
	vbox4->addLayout(hbox2);
	vbox4->addStretch(2);
	vbox4->addLayout(hbox1);
	vbox4->addStretch(6);

	this->setLayout(vbox4);
}

void loginPage::loginButtonClicked()
{
	emit navigateTo("Loading", 2);
}

void loginPage::signUpButtonClicked()
{
	emit navigateTo("Sign up", 1);
}