#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRect>
#include <string>
#include <map>
#include <QTextStream>
#include <QThread>

#include <iostream>


#include "playPage.h"
#include "task.h"

playPage::playPage(QWidget *parent):QFrame(parent)
{		
	card["cardBack"] = "images/cardback.svg";
	card["cardBack1"] = "images/cardback1.svg";	 
	card["Ad"] = "images/Ad.svg";
	card["2d"] = "images/2d.svg";
	card["3d"] = "images/3d.svg";
	card["4d"] = "images/4d.svg";
	card["5d"] = "images/5d.svg";
	card["6d"] = "images/6d.svg";
	card["7d"] = "images/7d.svg";
	card["8d"] = "images/8d.svg";
	card["9d"] = "images/9d.svg";
	card["Td"] = "images/10d.svg";
	card["Jd"] = "images/Jd.svg";
	card["Qd"] = "images/Qd.svg";
	card["Kd"] = "images/Kd.svg";

	card["Ac"] = "images/Ac.svg";
	card["2c"] = "images/2c.svg";
	card["3c"] = "images/3c.svg";
	card["4c"] = "images/4c.svg";
	card["5c"] = "images/5c.svg";
	card["6c"] = "images/6c.svg";
	card["7c"] = "images/7c.svg";
	card["8c"] = "images/8c.svg";
	card["9c"] = "images/9c.svg";
	card["Tc"] = "images/10c.svg";
	card["Jc"] = "images/Jc.svg";
	card["Qc"] = "images/Qc.svg";
	card["Kc"] = "images/Kc.svg";

	card["As"] = "images/As.svg";
	card["2s"] = "images/2s.svg";
	card["3s"] = "images/3s.svg";
	card["4s"] = "images/4s.svg";
	card["5s"] = "images/5s.svg";
	card["6s"] = "images/6s.svg";
	card["7s"] = "images/7s.svg";
	card["8s"] = "images/8s.svg";
	card["9s"] = "images/9s.svg";
	card["Ts"] = "images/10s.svg";
	card["Js"] = "images/Js.svg";
	card["Qs"] = "images/Qs.svg";
	card["Ks"] = "images/Ks.svg";

	card["Ah"] = "images/Ah.svg";
	card["2h"] = "images/2h.svg";
	card["3h"] = "images/3h.svg";
	card["4h"] = "images/4h.svg";
	card["5h"] = "images/5h.svg";
	card["6h"] = "images/6h.svg";
	card["7h"] = "images/7h.svg";
	card["8h"] = "images/8h.svg";
	card["9h"] = "images/9h.svg";
	card["Th"] = "images/10h.svg";
	card["Jh"] = "images/Jh.svg";
	card["Qh"] = "images/Qh.svg";
	card["Kh"] = "images/Kh.svg";

	nmOfPlayers = 4;

	bigBlind = 5;

	initUI();

}

playPage::~playPage()
{
}

void playPage::initUI()
{
	render = new renderWidget(nmOfPlayers);
	render->nmOfPlayers = 3;

	render->playerCard[0][0] = card["Ad"];
	render->playerCard[0][1] = card["4s"];

	render->playerCard[1][0] = card["cardBack"];
	render->playerCard[1][1] = card["cardBack"];

	render->playerCard[2][0] = card["7h"];
	render->playerCard[2][1] = card["Ks"];

	render->playerCard[3][0] = card["7d"];
	render->playerCard[3][1] = card["Kd"];

	render->tableCards[0] = card["cardBack"];
	render->tableCards[1] = card["cardBack"];
	render->tableCards[2] = card["cardBack"];
	render->tableCards[3] = card["cardBack"];
	render->tableCards[4] = card["cardBack"];

	render->userNames[0] = "janhencic";
	render->userNames[1] = "janjurman";
	render->userNames[2] = "jurekucer";
	render->userNames[3] = "alesruzic";

	render->userMoney[0] = 0;
	render->userMoney[1] = 0;
	render->userMoney[2] = 0;
	render->userMoney[3] = 0;

	render->bet[0] = "";
	render->bet[1] = "1000$";
	render->bet[2] = "10000$";
	render->bet[3] = "1000$";
	render->message = "";

	render->bet1[0] = 0;
	render->bet1[1] = 0;
	render->bet1[2] = 0;
	render->bet1[3] = 0;

	render->maxBet = 0;

	nekaj = 0;

	QVBoxLayout *vbox = new QVBoxLayout();

	QFont font;
	font.setPixelSize(40);

	bettAmmoutScroll = new QSlider();
	bettAmmoutScroll->setRange(0, 8);
	connect(bettAmmoutScroll, &QSlider::valueChanged, this, &playPage::betAmmountSlider);
	bettAmmoutScroll->setEnabled(false);



	bettAmmout = new QLabel("5$");
	bettAmmout->setAlignment(Qt::AlignCenter);
	bettAmmout->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	bettAmmout->setFont(font);
	
	bettAmmout->setStyleSheet("background: #FFFFFF; margin-top: 20px");

	raiseButton = new QPushButton("  Raise  ");
	raiseButton->setFont(font);
	raiseButton->setEnabled(false);
	raiseButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	raiseButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(raiseButton, &QPushButton::clicked, this, &playPage::raiseButtonClicked);

	checkButton = new QPushButton("  Check  ");
	checkButton->setFont(font);
	checkButton->setEnabled(false);
	checkButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	connect(checkButton, &QPushButton::clicked, this, &playPage::checkButtonClicked);
	checkButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	foldButton = new QPushButton("  Fold  ");
	foldButton->setFont(font);
	foldButton->setEnabled(false);
	foldButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	foldButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(foldButton, &QPushButton::clicked, this, &playPage::foldButtonClicked);



	QHBoxLayout * hbox  = new QHBoxLayout();
	hbox->addWidget(bettAmmoutScroll);
	hbox->addWidget(bettAmmout);
	hbox->addWidget(raiseButton);
	hbox->addWidget(checkButton);
	hbox->addWidget(foldButton);

	vbox->addWidget(render, 8);
	vbox->addLayout(hbox, 1);

	this->setLayout(vbox);
}

void playPage::draw(int nmOfPlayers, QString* userNames, int* playerSid, int mySid)
{
	render->nmOfPlayers = nmOfPlayers;
	int where = 0;
	for (int i = 0; i < nmOfPlayers; ++i)
	{
		if (mySid == playerSid[i])
		{
			where = i;
		}
	}

	for (int i = 0; i < nmOfPlayers; ++i)
	{
		render->userNames[((nmOfPlayers - where) + i) % nmOfPlayers] = userNames[i];
		render->playerSid[((nmOfPlayers - where) + i) % nmOfPlayers] = QString::number(playerSid[i]);

	}

	render->playerCard[0][0] = card["cardBack"];
	render->playerCard[0][1] = card["cardBack"];

	render->playerCard[1][0] = card["cardBack"];
	render->playerCard[1][1] = card["cardBack"];

	render->playerCard[2][0] = card["cardBack"];
	render->playerCard[2][1] = card["cardBack"];

	render->playerCard[3][0] = card["cardBack"];
	render->playerCard[3][1] = card["cardBack"];

	render->tableCards[0] = card["cardBack"];
	render->tableCards[1] = card["cardBack"];
	render->tableCards[2] = card["cardBack"];
	render->tableCards[3] = card["cardBack"];
	render->tableCards[4] = card["cardBack"];


	render->userMoney[0] = 1000;
	render->userMoney[1] = 1000;
	render->userMoney[2] = 1000;
	render->userMoney[3] = 1000;

	render->bet[0] = "";
	render->bet[1] = "";
	render->bet[2] = "";
	render->bet[3] = "";
	// this->repaint();
}

void playPage::raiseButtonClicked()
{
	int bet = bigBlind;

	for (int i = 0; i < bettAmmoutScroll->value(); ++i)
	{
		bet *= 2;
	}

	if (bet > render->userMoney[0])
	{
		bet = render->userMoney[0];
	}
	raiseButton->setEnabled(false);
	checkButton->setEnabled(false);
	foldButton->setEnabled(false);
	bettAmmoutScroll->setEnabled(false);

	server->sendRaiseMessage(bet - minBet);
}

void playPage::stackFocus()
{
	thread1 = new QThread();
	Task *task1 = new Task(server, this);
	task1->moveToThread(thread1);
	connect(thread1, SIGNAL (started()), task1, SLOT (doWork1()));
	thread1->start();
}

void playPage::checkButtonClicked()
{
	server->sendCheckMessage();
	raiseButton->setEnabled(false);
	checkButton->setEnabled(false);
	foldButton->setEnabled(false);
	bettAmmoutScroll->setEnabled(false);
}


void playPage::foldButtonClicked()
{	
	server->sendFoldMessage();
	raiseButton->setEnabled(false);
	checkButton->setEnabled(false);
	foldButton->setEnabled(false);
	bettAmmoutScroll->setEnabled(false);
}

void playPage::betAmmountSlider(int value)
{
	int bet = bigBlind;

	for (int i = 0; i < value; ++i)
	{
		bet *= 2;
	}

	if (bet > render->userMoney[0])
	{
		bet = render->userMoney[0];
	}
	// std::cout << bet << std::endl;
	bettAmmout->setText(QString::number(bet));
}

