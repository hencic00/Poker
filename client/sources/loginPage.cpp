#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRect>
#include <iostream>
#include <QSvgWidget>
#include <QRegExp>
#include <QRegExpValidator>
#include <QJsonObject>



#include "loginPage.h"

loginPage::loginPage(QWidget *parent):QFrame(parent)
{			 
	initUI();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
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


	emailInput = new QLineEdit();
	emailInput->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	emailInput->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	QRegExp re("[a-z0-9._%+-]*@?[a-z0-9.-]*\\.?[a-z]*");
	QRegExpValidator *validator = new QRegExpValidator(re, this);
	emailInput->setValidator(validator);
	emailInput->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	emailInput->setFont(font);
	emailInput->setPlaceholderText("E-mail");

	passwordInput = new QLineEdit();
	passwordInput->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	passwordInput->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	passwordInput->setFont(font);
	passwordInput->setEchoMode(QLineEdit::Password);
	passwordInput->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	passwordInput->setPlaceholderText("Password");


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


	QFont font1;
	font1.setPixelSize(20);
	alertLabel = new QLabel(this);
	QSizePolicy sp_retain = alertLabel->sizePolicy();
	sp_retain.setRetainSizeWhenHidden(true);
	alertLabel->setSizePolicy(sp_retain);
	alertLabel->setText("Fields are empty");
	alertLabel->setFont(font);
	alertLabel->setStyleSheet("color : #C73B3B");
	alertLabel->setAlignment(Qt::AlignCenter);
	alertLabel->setVisible(false);

	hbox->addWidget(loginButton);
	hbox->addWidget(signUpButton);


	QHBoxLayout *hbox1 = new QHBoxLayout();

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setSpacing(0);

	
	vbox->addWidget(emailInput);
	vbox->addWidget(passwordInput);


	vbox->addLayout(hbox);

	hbox1->addStretch(1);
	hbox1->addLayout(vbox);
	hbox1->addStretch(1);

	QVBoxLayout *vbox4 = new QVBoxLayout();
	vbox4->addStretch(6);
	vbox4->addLayout(hbox2);
	vbox4->addStretch(2);
	vbox4->addLayout(hbox1);
	vbox4->addStretch(1);
	vbox4->addWidget(alertLabel);
	vbox4->addStretch(6);

	this->setLayout(vbox4);
}

void loginPage::loginButtonClicked()
{
	if (emailInput->text().length() == 0 || passwordInput->text().length() == 0)
	{
		// std::cout << "fields empty" << std::endl;
		alertLabel->setText("Some fields are empty");
		alertLabel->setVisible(true);
	}
	else 
	{
		QJsonObject obj = server->login(emailInput->text(), passwordInput->text());

		QJsonValue val = obj.value("status");

		if (val.toString() == "ok")
		{
			alertLabel->setVisible(false);
			QJsonValue val1 = obj.value("userId");
			QJsonValue val2 = obj.value("username");

			strcpy(email, emailInput->text().toStdString().c_str());
			strcpy(userId, val1.toString().toStdString().c_str());
			strcpy(userName, val2.toString().toStdString().c_str());

			stack->setCurrentIndex(2);
			timer->start(500);
		}
		else if(val.toString() == "nonExistentUser")
		{
			alertLabel->setText("Email or password do not match");
			alertLabel->setVisible(true);
		}
		else if (val.toString() == "wrongPassword")
		{
			alertLabel->setText("Email or password do not match");
			alertLabel->setVisible(true);
		}
		else{}
	}

}

void loginPage::timeOut()
{	
	stack->setCurrentIndex(5);
	timer->stop();
}

void loginPage::signUpButtonClicked()
{
	alertLabel->setVisible(false);
	emit navigateTo("Sign up", 1);
}