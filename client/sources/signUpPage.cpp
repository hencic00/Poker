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

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 9999

#include "signUpPage.h"

void test()
{
	struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;


    char *hello = "{\"username\": \"plesJesus\", \"password\": \"plesJesus\", \"email\": \"plesJesus\", \"agenda\": \"register\"}";
    int length = strlen(hello);

    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }

    send(sock , (char*) &length , 4 , 0 );
    // send(sock , (char*) length , 4 , 0 );
    // send(sock , (char*) length , 4 , 0 );
    // send(sock , (char*) length , 4 , 0 );
    send(sock , hello , length , 0 );

    int responseLength = 0;
    int responseLength1 = 0;


    recv(sock, (char*) &responseLength, 4, 0);
    responseLength1 |= ((responseLength >> 3 * 8) & 0x000000ff);
    responseLength1 |= ((responseLength >> 1 * 8) & 0x0000ff00);
    responseLength1 |= ((responseLength << 1 * 8) & 0x00ff0000);
    responseLength1 |= ((responseLength << 3 * 8) & 0xff000000);

    std::cout << responseLength1 << std::endl;

}

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

	QPushButton* signUpButton = new QPushButton("  Apply  ");
	signUpButton->setFont(font);
	signUpButton->setIcon(QIcon("./images/confirm.svg"));
	signUpButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	signUpButton->setFixedSize(rec.width() * 0.125, rec.height()*0.09);
	signUpButton->setIconSize(QSize(rec.height()*0.05, rec.height()*0.05));
	signUpButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(signUpButton, &QPushButton::clicked, this, &signUpPage::applyButtonClicked);


	hbox->addWidget(backButton);
	hbox->addWidget(signUpButton);


	QHBoxLayout *hbox1 = new QHBoxLayout();

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->setSpacing(0);

	
	vbox->addWidget(email);
	vbox->addWidget(password);
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
	vbox4->addStretch(6);

	this->setLayout(vbox4);
}

void signUpPage::applyButtonClicked()
{
	test();
}

void signUpPage::backButtonClicked()
{
	emit navigateTo("Login", 0);
}