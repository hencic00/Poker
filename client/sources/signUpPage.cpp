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

#include "signUpPage.h"



signUpPage::signUpPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

signUpPage::~signUpPage()
{}

void signUpPage::initUI()
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
	emailInput->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	emailInput->setFont(font);
	QRegExp re("[a-z0-9._%+-]*@?[a-z0-9.-]*\\.?[a-z]*");
	QRegExpValidator *validator = new QRegExpValidator(re, this);
	emailInput->setValidator(validator);
	emailInput->setPlaceholderText("E-mail");

	userNameInput = new QLineEdit();
	userNameInput->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	userNameInput->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	userNameInput->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	userNameInput->setFont(font);
	QRegExp re2("[a-z0-9]*");
	QRegExpValidator *validator2 = new QRegExpValidator(re2, this);
	userNameInput->setValidator(validator2);
	userNameInput->setPlaceholderText("User name");

	passwordInput = new QLineEdit();
	passwordInput->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	passwordInput->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	passwordInput->setFont(font);
	passwordInput->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	QRegExp re1("/^[\x21-\x7E]+$/");
	QRegExpValidator *validator1 = new QRegExpValidator(re, this);
	passwordInput->setEchoMode(QLineEdit::Password);
	passwordInput->setValidator(validator1);
	passwordInput->setPlaceholderText("Password");


	passwordRe = new QLineEdit();
	passwordRe->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	passwordRe->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	passwordRe->setFont(font);
	passwordRe->setEchoMode(QLineEdit::Password);
	passwordRe->setValidator(validator1);
	passwordRe->setFixedSize(rec.width() * 0.25, rec.height()*0.07);
	passwordRe->setPlaceholderText("Retype password");

	QHBoxLayout *hbox = new QHBoxLayout();

	QPushButton* backButton = new QPushButton("  Back  ");
	backButton->setFont(font);
	backButton->setIcon(QIcon("./images/back.svg"));
	backButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	backButton->setFixedSize(rec.width() * 0.125, rec.height()*0.09);
	backButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	backButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(backButton, &QPushButton::clicked, this, &signUpPage::backButtonClicked);

	QPushButton* signUpButton = new QPushButton("  Apply  ");
	signUpButton->setFont(font);
	signUpButton->setIcon(QIcon("./images/confirm.svg"));
	signUpButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	signUpButton->setFixedSize(rec.width() * 0.125, rec.height()*0.09);
	signUpButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	signUpButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(signUpButton, &QPushButton::clicked, this, &signUpPage::applyButtonClicked);

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


	hbox->addWidget(backButton);
	hbox->addWidget(signUpButton);


	QHBoxLayout *hbox1 = new QHBoxLayout();

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setSpacing(0);

	
	vbox->addWidget(emailInput);
	vbox->addWidget(userNameInput);
	vbox->addWidget(passwordInput);
	vbox->addWidget(passwordRe);
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

void signUpPage::applyButtonClicked()
{
	if (emailInput->text().length() == 0 || passwordInput->text().length() == 0 || passwordRe->text().length() == 0)
	{
		alertLabel->setText("Some fields are empty");
		alertLabel->setVisible(true);
	}
	else if (passwordInput->text() != passwordRe->text())
	{
		std::cout << "passwords do not match" << std::endl;

		alertLabel->setText("Passwords do not match");
		alertLabel->setVisible(true);
	}
	else
	{
		QJsonObject obj = server->signUp(userNameInput->text(), emailInput->text(), passwordInput->text());
		QJsonValue val = obj.value("status");

		if (val.toString() == "emailTaken")
		{
			alertLabel->setText("Email already in use");
			alertLabel->setVisible(true);
		}
		else
		{
			QJsonValue val1 = obj.value("userId");

			strcpy(email, emailInput->text().toStdString().c_str());
			strcpy(userName, userNameInput->text().toStdString().c_str());
			strcpy(userId, val1.toString().toStdString().c_str());

			emit navigateTo("Loading", 2);

			alertLabel->setVisible(false);
		}
	}

}

void signUpPage::backButtonClicked()
{
	emit navigateTo("Login", 0);
	alertLabel->setVisible(false);
}