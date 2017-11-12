#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRect>
#include <string>
#include <map>
#include <QTextStream>

#include <iostream>


#include "playPage.h"

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
	card["10d"] = "images/10d.svg";
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
	card["10c"] = "images/10c.svg";
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
	card["10s"] = "images/10s.svg";
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
	card["10h"] = "images/10h.svg";
	card["Jh"] = "images/Jh.svg";
	card["Qh"] = "images/Qh.svg";
	card["Kh"] = "images/Kh.svg";

	tableCards[0] = card["Ad"];
	tableCards[1] = card["8h"];
	tableCards[2] = card["4s"];
	tableCards[3] = card["cardBack"];
	tableCards[4] = card["cardBack"];

	initUI();

}

playPage::~playPage()
{
}

void playPage::initUI()
{
	render = new renderWidget();
	render->tableCards = tableCards;
	nekaj = 0;

	QVBoxLayout *vbox = new QVBoxLayout();

	QFont font;
	font.setPixelSize(40);

	QPushButton* raiseButton = new QPushButton("  Raise  ");
	raiseButton->setFont(font);
	raiseButton->setIcon(QIcon("./images/key.svg"));
	raiseButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	raiseButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
	connect(raiseButton, &QPushButton::clicked, this, &playPage::raiseButtonClicked);

	QPushButton* checkButton = new QPushButton("  Check  ");
	checkButton->setFont(font);
	checkButton->setIcon(QIcon("./images/key.svg"));
	checkButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	checkButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	QPushButton* foldButton = new QPushButton("  Fold  ");
	foldButton->setFont(font);
	foldButton->setIcon(QIcon("./images/key.svg"));
	foldButton->setStyleSheet("margin-top: 20px; margin-right: 10px;");
	foldButton->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );

	QHBoxLayout * hbox  = new QHBoxLayout();
	hbox->addWidget(raiseButton);
	hbox->addWidget(checkButton);
	hbox->addWidget(foldButton);

	vbox->addWidget(render, 8);
	vbox->addLayout(hbox, 1);

	this->setLayout(vbox);
}

void playPage::raiseButtonClicked()
{
	if(nekaj == 0)
	{
		tableCards[0] = card["Ac"];
		tableCards[1] = card["Ac"];
		tableCards[2] = card["2d"];
		tableCards[3] = card["Ac"];
		tableCards[4] = card["As"];

		nekaj = 1;
	}
	else
	{
		tableCards[0] = card["Kd"];
		tableCards[1] = card["Kc"];
		tableCards[2] = card["cardBack"];
		tableCards[3] = card["cardBack1"];
		tableCards[4] = card["Ks"];

		nekaj = 0;

	}


	render->tableCards = tableCards;
	render->repaint();
}
