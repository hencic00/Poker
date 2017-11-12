#define _BSD_SOURCE

#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>

#include "renderWidget.h"

renderWidget::renderWidget()
{
	w = QApplication::desktop()->screenGeometry().width();
	h = QApplication::desktop()->screenGeometry().height();
	this->setStyleSheet("background-color: #C3C3C3");
}

renderWidget::~renderWidget()
{}

void renderWidget::paintEvent(QPaintEvent *e)
{
	QPainter qp(this);
	qp.setPen(QColor("#D60000"));
	qp.setBrush(QBrush("#B55151"));

	qp.translate(this->width()/2, this->height()/2);


	QSvgRenderer table(QString("images/pokerTableBlank.svg"));

	QSvgRenderer tableCard(tableCards[0]);
	QSvgRenderer tableCard1(tableCards[1]);
	QSvgRenderer tableCard2(tableCards[2]);
	QSvgRenderer tableCard3(tableCards[3]);
	QSvgRenderer tableCard4(tableCards[4]);

	QSvgRenderer playerCard(tableCards[4]);
	QSvgRenderer playerCard1(tableCards[4]);

	double faktor = w * 0.0004;

	// qp.rotate(-8);

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
	tableCard3.render(&qp, rect6);
	qp.rotate(8);
	qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
	tableCard3.render(&qp, rect7);

	qp.translate(-tableCard3.defaultSize().rwidth() * 7.4 * faktor, -tableCard3.defaultSize().rheight()*faktor*2.3);
	qp.rotate(-8);
	tableCard3.render(&qp, rect7);
	qp.rotate(8);
	qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
	tableCard3.render(&qp, rect7);

	qp.translate(tableCard3.defaultSize().rwidth() * 5.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*2.3);
	qp.rotate(-8);
	tableCard3.render(&qp, rect6);
	qp.rotate(8);
	qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
	tableCard3.render(&qp, rect7);

	qp.translate(tableCard3.defaultSize().rwidth() * 6 * faktor, +tableCard3.defaultSize().rheight()*faktor*2.4);
	qp.rotate(-8);
	tableCard3.render(&qp, rect6);
	qp.rotate(8);
	qp.translate(tableCard3.defaultSize().rwidth()*0.8 * faktor, -tableCard3.defaultSize().rheight()*faktor*0.05);
	tableCard3.render(&qp, rect7);


	
}