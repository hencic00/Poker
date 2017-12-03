#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>
#include <QJsonObject>
#include <QJsonValue>

#include <iostream>

#include "indexPage.h"
#include "lobbiesPage.h"

indexPage::indexPage(QWidget *parent):QFrame(parent)
{			 
	initUI();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
}

indexPage::~indexPage()
{}

void indexPage::initUI()
{	

	QRect rec = QApplication::desktop()->screenGeometry();

	QFont font;
	font.setPixelSize(40);
	QFont font1;
	font1.setPixelSize(100);

	QHBoxLayout *hbox = new QHBoxLayout();
	QVBoxLayout *vbox = new QVBoxLayout();

	welcomeBanner = new QLabel();
	
	welcomeBanner->setFont(font1);
	welcomeBanner->setAlignment(Qt::AlignCenter);
	welcomeBanner->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	QPushButton* joinLobbyButton = new QPushButton("  Join lobby  ");
	joinLobbyButton->setFont(font);
	joinLobbyButton->setFixedSize(rec.width() * 0.3, rec.height()*0.09);
	joinLobbyButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(joinLobbyButton, &QPushButton::clicked, this, &indexPage::joinLobbyButtonClicked);

	QPushButton* logoutButton = new QPushButton("  Logout  ");
	logoutButton->setFont(font);
	logoutButton->setFixedSize(rec.width() * 0.3, rec.height()*0.09);
	logoutButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(logoutButton, &QPushButton::clicked, this, &indexPage::logoutButtonPressed);


	vbox->addStretch(6);
	vbox->addWidget(welcomeBanner);
	vbox->addStretch(1);
	vbox->addWidget(joinLobbyButton);
	vbox->addWidget(logoutButton);
	vbox->addStretch(6);

	hbox->addStretch(1);
	hbox->addLayout(vbox);
	hbox->addStretch(1);

	this->setLayout(hbox);
}

void indexPage::paintEvent(QPaintEvent *e)
{	
	QString str = QString(userName);
	welcomeBanner->setText("Welcome back \n" + str);
}

void indexPage::timeOut()
{
	stack->setCurrentIndex(0);
	timer->stop();
}

void indexPage::logoutButtonPressed()
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

void indexPage::joinLobbyButtonClicked()
{
	stack->setCurrentIndex(3);
	
	((lobbiesPage*)stack->widget(3))->stackFocus();
}