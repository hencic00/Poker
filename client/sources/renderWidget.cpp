#define _BSD_SOURCE

#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>

#include "renderWidget.h"

renderWidget::renderWidget(int nm)
{
	w = QApplication::desktop()->screenGeometry().width();
	h = QApplication::desktop()->screenGeometry().height();
	this->setStyleSheet("background-color: #C3C3C3");

	nmOfPlayers = 4;
}

renderWidget::~renderWidget()
{}

void renderWidget::paintEvent(QPaintEvent *e)
{
	QPainter qp(this);
	qp.setPen(QColor("#000000"));
	qp.setBrush(QBrush("#000000"));

	qp.translate(this->width()/2, this->height()/2);


	QSvgRenderer table(QString("images/pokerTableBlank.svg"));

	QSvgRenderer avatar(QString("images/maleAvatar.svg"));
	QSvgRenderer delaerChip(QString("images/dealerChip.svg"));

	QSvgRenderer tableCard(tableCards[0]);
	QSvgRenderer tableCard1(tableCards[1]);
	QSvgRenderer tableCard2(tableCards[2]);
	QSvgRenderer tableCard3(tableCards[3]);
	QSvgRenderer tableCard4(tableCards[4]);

	double faktor = w * 0.0004;

	

	if (nmOfPlayers == 2)
	{
		QSvgRenderer playerCard00(playerCard[0][0]);
		QSvgRenderer playerCard01(playerCard[0][1]);

		QSvgRenderer playerCard10(playerCard[1][0]);
		QSvgRenderer playerCard11(playerCard[1][1]);

		QRect rect(-table.defaultSize().rwidth()/2 * faktor, -table.defaultSize().rheight()/2*faktor, table.defaultSize().rwidth()*faktor, table.defaultSize().rheight() *faktor);

		QRect rect1(-tableCard.defaultSize().rwidth()*2.5  * faktor, -tableCard.defaultSize().rheight()/2*faktor, tableCard.defaultSize().rwidth()*faktor, tableCard.defaultSize().rheight() *faktor);
		QRect rect2(-tableCard1.defaultSize().rwidth()*1.5  * faktor, -tableCard1.defaultSize().rheight()/2*faktor, tableCard1.defaultSize().rwidth()*faktor, tableCard1.defaultSize().rheight() *faktor);
		QRect rect3(-tableCard2.defaultSize().rwidth()*0.5 * faktor, -tableCard2.defaultSize().rheight()/2*faktor, tableCard2.defaultSize().rwidth()*faktor, tableCard2.defaultSize().rheight() *faktor);
		QRect rect4(+tableCard3.defaultSize().rwidth()*0.5 * faktor, -tableCard3.defaultSize().rheight()/2*faktor, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);
		QRect rect5(+tableCard4.defaultSize().rwidth()*1.5 * faktor, -tableCard4.defaultSize().rheight()/2*faktor, tableCard4.defaultSize().rwidth()*faktor, tableCard4.defaultSize().rheight() *faktor);

		QRect rect6(0, 0, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);
		QRect rect7(0, 0, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);

		QRect rect8(-tableCard.defaultSize().rwidth()*6.5  * faktor, -tableCard.defaultSize().rheight()/2*faktor, tableCard.defaultSize().rwidth()*faktor, tableCard.defaultSize().rheight() *faktor);
		QRect rect9(-tableCard1.defaultSize().rwidth()*7.5  * faktor, -tableCard1.defaultSize().rheight()/2*faktor, tableCard1.defaultSize().rwidth()*faktor, tableCard1.defaultSize().rheight() *faktor);

		table.render(&qp, rect);

		tableCard.render(&qp, rect1);
		tableCard1.render(&qp, rect2);
		tableCard2.render(&qp, rect3);
		tableCard3.render(&qp, rect4);
		tableCard4.render(&qp, rect5);

		qp.translate(-tableCard3.defaultSize().rwidth()*1 * faktor, tableCard3.defaultSize().rheight()*faktor*1.85);
		qp.rotate(-8);
		playerCard00.render(&qp, rect6);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard01.render(&qp, rect7);

		QFont font = qp.font() ;
	 	font.setPointSize ( faktor * 13 );
	 	qp.setFont(font);
	 	QFontMetrics fm(font);

	 	qp.drawText(QPoint(-fm.width(message) * faktor * 0.325 + faktor * 12, -tableCard3.defaultSize().rheight() * faktor * 2.4), message);

	 	font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(userNames[0]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), userNames[0]);
		font.setBold(false);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(QString::number(userMoney[0])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.7), QString::number(userMoney[0]) + " $");
		qp.drawText(QPoint(-fm.width(bet[0]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), bet[0]);

		qp.translate(tableCard3.defaultSize().rwidth()*(-0.8) * faktor, -tableCard3.defaultSize().rheight()*faktor*4.6);
		qp.rotate(-8);
		playerCard10.render(&qp, rect7);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard11.render(&qp, rect7);

	 	QFontMetrics fm1(font);

	 	font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm1.width(userNames[1]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.55), userNames[1]);
		font.setBold(false);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm1.width(QString::number(userMoney[1])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), QString::number(userMoney[1]) + " $");
		qp.drawText(QPoint(-fm1.width(bet[1]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), bet[1]);

	}
	else if(nmOfPlayers == 3)
	{
		QSvgRenderer playerCard00(playerCard[0][0]);
		QSvgRenderer playerCard01(playerCard[0][1]);

		QSvgRenderer playerCard10(playerCard[1][0]);
		QSvgRenderer playerCard11(playerCard[1][1]);

		QSvgRenderer playerCard20(playerCard[2][0]);
		QSvgRenderer playerCard21(playerCard[2][1]);

		QRect rect(-table.defaultSize().rwidth()/2 * faktor, -table.defaultSize().rheight()/2*faktor, table.defaultSize().rwidth()*faktor, table.defaultSize().rheight() *faktor);

		QRect rect1(-tableCard.defaultSize().rwidth()*2.5  * faktor, -tableCard.defaultSize().rheight()/2*faktor, tableCard.defaultSize().rwidth()*faktor, tableCard.defaultSize().rheight() *faktor);
		QRect rect2(-tableCard1.defaultSize().rwidth()*1.5  * faktor, -tableCard1.defaultSize().rheight()/2*faktor, tableCard1.defaultSize().rwidth()*faktor, tableCard1.defaultSize().rheight() *faktor);
		QRect rect3(-tableCard2.defaultSize().rwidth()*0.5 * faktor, -tableCard2.defaultSize().rheight()/2*faktor, tableCard2.defaultSize().rwidth()*faktor, tableCard2.defaultSize().rheight() *faktor);
		QRect rect4(+tableCard3.defaultSize().rwidth()*0.5 * faktor, -tableCard3.defaultSize().rheight()/2*faktor, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);
		QRect rect5(+tableCard4.defaultSize().rwidth()*1.5 * faktor, -tableCard4.defaultSize().rheight()/2*faktor, tableCard4.defaultSize().rwidth()*faktor, tableCard4.defaultSize().rheight() *faktor);

		QRect rect6(0, 0, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);
		QRect rect7(0, 0, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);

		QRect rect8(-tableCard.defaultSize().rwidth()*6.5  * faktor, -tableCard.defaultSize().rheight()/2*faktor, tableCard.defaultSize().rwidth()*faktor, tableCard.defaultSize().rheight() *faktor);
		QRect rect9(-tableCard1.defaultSize().rwidth()*7.5  * faktor, -tableCard1.defaultSize().rheight()/2*faktor, tableCard1.defaultSize().rwidth()*faktor, tableCard1.defaultSize().rheight() *faktor);

		table.render(&qp, rect);

		tableCard.render(&qp, rect1);
		tableCard1.render(&qp, rect2);
		tableCard2.render(&qp, rect3);
		tableCard3.render(&qp, rect4);
		tableCard4.render(&qp, rect5);

		qp.translate(-tableCard3.defaultSize().rwidth()*1 * faktor, tableCard3.defaultSize().rheight()*faktor*1.85);
		qp.rotate(-8);
		playerCard00.render(&qp, rect6);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard01.render(&qp, rect7);

		QFont font = qp.font() ;
	 	font.setPointSize ( faktor * 13 );
	 	qp.setFont(font);
	 	QFontMetrics fm(font);

	 	qp.drawText(QPoint(-fm.width(message) * faktor * 0.325 + faktor * 12, -tableCard3.defaultSize().rheight() * faktor * 2.4), message);

	 	font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(userNames[0]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), userNames[0]);
		font.setBold(false);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(QString::number(userMoney[0])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.7), QString::number(userMoney[0]) + " $");
		qp.drawText(QPoint(-fm.width(bet[0]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), bet[0]);

		qp.translate(tableCard3.defaultSize().rwidth()*(-7.3) * faktor, -tableCard3.defaultSize().rheight()*faktor*3.5);
		qp.rotate(-8);
		playerCard10.render(&qp, rect7);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard11.render(&qp, rect7);

	 	QFontMetrics fm1(font);

	 	font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm1.width(userNames[1]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.55), userNames[1]);
		font.setBold(false);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm1.width(QString::number(userMoney[1])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), QString::number(userMoney[1]) + " $");
		qp.drawText(QPoint(faktor * 105, tableCard3.defaultSize().rheight() * faktor * 0.67), bet[1]);


		qp.translate(tableCard3.defaultSize().rwidth()*(12.3) * faktor, 0);
		qp.rotate(-8);
		playerCard20.render(&qp, rect6);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard21.render(&qp, rect7);

	 	QFontMetrics fm2(font);

	 	font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm2.width(userNames[2]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.55), userNames[2]);
		font.setBold(false);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm2.width(QString::number(userMoney[2])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), QString::number(userMoney[2]) + " $");
		qp.drawText(QPoint(-fm.width(bet[2]) * faktor * 0.65 - faktor * 77, tableCard3.defaultSize().rheight() * faktor * 0.67), bet[2]);
	}
	else if(nmOfPlayers == 4)
	{
		QSvgRenderer playerCard00(playerCard[0][0]);
		QSvgRenderer playerCard01(playerCard[0][1]);

		QSvgRenderer playerCard10(playerCard[1][0]);
		QSvgRenderer playerCard11(playerCard[1][1]);

		QSvgRenderer playerCard20(playerCard[2][0]);
		QSvgRenderer playerCard21(playerCard[2][1]);

		QSvgRenderer playerCard30(playerCard[3][0]);
		QSvgRenderer playerCard31(playerCard[3][1]);

		QRect rect(-table.defaultSize().rwidth()/2 * faktor, -table.defaultSize().rheight()/2*faktor, table.defaultSize().rwidth()*faktor, table.defaultSize().rheight() *faktor);

		QRect rect1(-tableCard.defaultSize().rwidth()*2.5  * faktor, -tableCard.defaultSize().rheight()/2*faktor, tableCard.defaultSize().rwidth()*faktor, tableCard.defaultSize().rheight() *faktor);
		QRect rect2(-tableCard1.defaultSize().rwidth()*1.5  * faktor, -tableCard1.defaultSize().rheight()/2*faktor, tableCard1.defaultSize().rwidth()*faktor, tableCard1.defaultSize().rheight() *faktor);
		QRect rect3(-tableCard2.defaultSize().rwidth()*0.5 * faktor, -tableCard2.defaultSize().rheight()/2*faktor, tableCard2.defaultSize().rwidth()*faktor, tableCard2.defaultSize().rheight() *faktor);
		QRect rect4(+tableCard3.defaultSize().rwidth()*0.5 * faktor, -tableCard3.defaultSize().rheight()/2*faktor, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);
		QRect rect5(+tableCard4.defaultSize().rwidth()*1.5 * faktor, -tableCard4.defaultSize().rheight()/2*faktor, tableCard4.defaultSize().rwidth()*faktor, tableCard4.defaultSize().rheight() *faktor);

		QRect rect6(0, 0, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);
		QRect rect7(0, 0, tableCard3.defaultSize().rwidth()*faktor, tableCard3.defaultSize().rheight() *faktor);

		QRect rect8(-tableCard.defaultSize().rwidth()*6.5  * faktor, -tableCard.defaultSize().rheight()/2*faktor, tableCard.defaultSize().rwidth()*faktor, tableCard.defaultSize().rheight() *faktor);
		QRect rect9(-tableCard1.defaultSize().rwidth()*7.5  * faktor, -tableCard1.defaultSize().rheight()/2*faktor, tableCard1.defaultSize().rwidth()*faktor, tableCard1.defaultSize().rheight() *faktor);

		table.render(&qp, rect);

		tableCard.render(&qp, rect1);
		tableCard1.render(&qp, rect2);
		tableCard2.render(&qp, rect3);
		tableCard3.render(&qp, rect4);
		tableCard4.render(&qp, rect5);

		qp.translate(-tableCard3.defaultSize().rwidth()*1 * faktor, tableCard3.defaultSize().rheight()*faktor*1.8);
		qp.rotate(-8);
		playerCard00.render(&qp, rect6);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard01.render(&qp, rect7);

		QFont font = qp.font() ;
	 	font.setPointSize ( faktor * 13 );
	 	font.setBold(true);
	 	qp.setFont(font);
	 	QFontMetrics fm(font);

	 	qp.drawText(QPoint(-fm.width(message) * faktor * 0.325 + faktor * 12, -tableCard3.defaultSize().rheight() * faktor * 2.4), message);

		qp.drawText(QPoint(-fm.width(userNames[0]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), userNames[0]);
		font.setBold(false);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(QString::number(userMoney[0])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.7), QString::number(userMoney[0]) + " $");

		qp.drawText(QPoint(-fm.width(bet[0]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), bet[0]);

		qp.translate(-tableCard3.defaultSize().rwidth() * 7.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*2.3);
		qp.rotate(-8);
		playerCard10.render(&qp, rect7);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard11.render(&qp, rect7);

		font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(userNames[1]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), userNames[1]);
		font.setBold(false);
		qp.setFont(font);
		qp.drawText(QPoint(-fm.width(QString::number(userMoney[1])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.7), QString::number(userMoney[1]) + " $");
		qp.drawText(QPoint(faktor * 105, tableCard3.defaultSize().rheight() * faktor * 0.67), bet[1]);

		qp.translate(tableCard3.defaultSize().rwidth() * 6.2 * faktor, -tableCard3.defaultSize().rheight()*faktor*2.3);
		qp.rotate(-8);
		playerCard20.render(&qp, rect6);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard21.render(&qp, rect7);

		font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(userNames[2]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.55), userNames[2]);
		font.setBold(false);
		qp.setFont(font);
		qp.drawText(QPoint(-fm.width(QString::number(userMoney[2])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * -0.2), QString::number(userMoney[2]) + " $");

		qp.drawText(QPoint(-fm.width(bet[2]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), bet[2]);

		qp.translate(tableCard3.defaultSize().rwidth() * 6.4 * faktor, +tableCard3.defaultSize().rheight()*faktor*2.4);
		qp.rotate(-8);
		playerCard30.render(&qp, rect6);
		qp.rotate(8);
		qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
		playerCard31.render(&qp, rect7);

		font.setBold(true);
	 	qp.setFont(font);
		qp.drawText(QPoint(-fm.width(userNames[3]) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.35), userNames[3]);
		font.setBold(false);
		qp.setFont(font);
		qp.drawText(QPoint(-fm.width(QString::number(userMoney[3])) * faktor * 0.325 + faktor * 12, tableCard3.defaultSize().rheight() * faktor * 1.7), QString::number(userMoney[3]) + " $");

		qp.drawText(QPoint(-fm.width(bet[3]) * faktor * 0.65 - faktor * 77, tableCard3.defaultSize().rheight() * faktor * 0.67), bet[3]);
	}


}