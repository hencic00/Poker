#pragma once

#include <QFrame>
#include <QRect>
#include <QSvgRenderer>
#include <string>

class renderWidget : public QFrame
{

	Q_OBJECT

	public:
		renderWidget(int nm);
		~renderWidget();

		QString nekaj;
		QString tableCards[5];
		QString playerCard[5][2];
		QString userNames[10];
		QString playerSid[10];
		double userMoney[10];
		QString bet[10];
		double bet1[10];
		double maxBet;
		int nmOfPlayers;
		QString message;
		QString boxColor[10];

	private:
		int w;
		int h;


		void paintEvent(QPaintEvent *e);

};