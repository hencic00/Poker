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
#include <QtGui>
#include <QSvgRenderer>
#include <string>

#include <iostream>


#include "playPage.h"



class renderWidget : public QFrame
{
	public:
		renderWidget()
		{
			w = QApplication::desktop()->screenGeometry().width();
			h = QApplication::desktop()->screenGeometry().height();
			setStyleSheet("background-color: #C3C3C3");
		}
		~renderWidget()
		{

		}

		std::string nekaj;

	private:
		int w;
		int h;


		void paintEvent(QPaintEvent *e)
		{
			QPainter qp(this);
			qp.setPen(QColor("#D60000"));
			qp.setBrush(QBrush("#B55151"));

			qp.translate(this->width()/2, this->height()/2);


			QSvgRenderer table(QString("images/pokerTableBlank.svg"));
			QSvgRenderer card(QString("images/clubAce.svg"));
			// QSvgRenderer card1(QString("images/diamondAce.svg"));
			// QPixmap pm(1286, 595);

			double faktor = w * 0.0004;
			// std::cout << faktor << std::endl;

			QRect rect(-table.defaultSize().rwidth()/2 * faktor, -table.defaultSize().rheight()/2*faktor, table.defaultSize().rwidth()*faktor, table.defaultSize().rheight() *faktor);
			QRect rect1(-card.defaultSize().rwidth()*2.5  * faktor, -card.defaultSize().rheight()/2*faktor, card.defaultSize().rwidth()*faktor, card.defaultSize().rheight() *faktor);
			QRect rect2(-card.defaultSize().rwidth()*1.5  * faktor, -card.defaultSize().rheight()/2*faktor, card.defaultSize().rwidth()*faktor, card.defaultSize().rheight() *faktor);
			QRect rect3(-card.defaultSize().rwidth()*0.5 * faktor, -card.defaultSize().rheight()/2*faktor, card.defaultSize().rwidth()*faktor, card.defaultSize().rheight() *faktor);
			QRect rect4(+card.defaultSize().rwidth()*0.5 * faktor, -card.defaultSize().rheight()/2*faktor, card.defaultSize().rwidth()*faktor, card.defaultSize().rheight() *faktor);
			QRect rect5(+card.defaultSize().rwidth()*1.5 * faktor, -card.defaultSize().rheight()/2*faktor, card.defaultSize().rwidth()*faktor, card.defaultSize().rheight() *faktor);

			table.render(&qp, rect);
			card.render(&qp, rect1);
			card.render(&qp, rect2);
			card.render(&qp, rect3);
			card.render(&qp, rect4);
			card.render(&qp, rect5);
		}

};

playPage::playPage(QWidget *parent):QFrame(parent)
{			 
	
	initUI();
}

playPage::~playPage()
{
}

void playPage::initUI()
{
	renderWidget* render = new renderWidget();
	render->nekaj = "images/clubAce.svg";

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
	// images/diamondAce.svg
}
