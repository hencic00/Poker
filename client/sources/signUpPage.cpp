#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRect>
#include <iostream>


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


	QLineEdit* passwordRe = new QLineEdit();
	passwordRe->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	passwordRe->setStyleSheet("margin-bottom: 20px; padding: 30px;");
	passwordRe->setFont(font);
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

	QPushButton* signUpButton = new QPushButton("  Sign up  ");
	signUpButton->setFont(font);
	signUpButton->setIcon(QIcon("./images/confirm.svg"));
	signUpButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	signUpButton->setFixedSize(rec.width() * 0.125, rec.height()*0.09);
	signUpButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	signUpButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	hbox->addWidget(backButton);
	hbox->addWidget(signUpButton);


	QHBoxLayout *hbox1 = new QHBoxLayout();

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setSpacing(0);

	vbox->addStretch(1);
	vbox->addWidget(email);
	vbox->addWidget(password);
	vbox->addWidget(passwordRe);
	vbox->addLayout(hbox);
	vbox->addStretch(1);

	hbox1->addStretch(1);
	hbox1->addLayout(vbox);
	hbox1->addStretch(1);

	this->setLayout(hbox1);
}

void signUpPage::backButtonClicked()
{
	emit navigateTo("Login", 0);
}