#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRect>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSvgWidget>
#include <iostream>


#include "lobbyPage.h"

lobbyPage::lobbyPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

lobbyPage::~lobbyPage()
{}

void lobbyPage::initUI()
{

	QRect rec = QApplication::desktop()->screenGeometry();

	QFont font;
	font.setPixelSize(40);

	QHBoxLayout *hbox = new QHBoxLayout();

	QPushButton* joinButton = new QPushButton("  Join lobby  ");
	joinButton->setFont(font);
	joinButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	joinButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );


	QPushButton* createButton = new QPushButton("  Create lobby  ");
	createButton->setFont(font);
	createButton->setStyleSheet("margin-top: 20px; margin-left: 10px;");
	createButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(createButton, &QPushButton::clicked, this, &lobbyPage::createButtonClicked);


	hbox->addWidget(joinButton);
	hbox->addWidget(createButton);	


	QListWidget *listWidget = new QListWidget(this);

	QListWidgetItem *newItem = new QListWidgetItem;
	newItem->setText("Lobby 1");
	newItem->setFont(font);

	QListWidgetItem *newItem1 = new QListWidgetItem;
    newItem1->setText("Lobby 2");
	newItem1->setFont(font);

	QListWidgetItem *newItem2 = new QListWidgetItem;
    newItem2->setText("Lobby 3");
	newItem2->setFont(font);

	QListWidgetItem *newItem3 = new QListWidgetItem;
    newItem3->setText("Lobby 4");
	newItem3->setFont(font);

    listWidget->insertItem(0, newItem);
    listWidget->insertItem(0, newItem1);
    listWidget->insertItem(0, newItem2);
    listWidget->insertItem(0, newItem3);

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(listWidget, 5);
	vbox->addLayout(hbox, 1);
	this->setLayout(vbox);
}

void lobbyPage::createButtonClicked()
{
	emit navigateTo("Playing", 4);
}