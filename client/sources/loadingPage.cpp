#define _BSD_SOURCE

#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QMovie>
#include <QtSvg>

#include "loadingPage.h"

loadingPage::loadingPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

loadingPage::~loadingPage()
{}

void loadingPage::initUI()
{
	QVBoxLayout *vbox = new QVBoxLayout();

	QLabel *lbl = new QLabel();
	QMovie *movie = new QMovie("./images/spinner.gif");
	movie->setSpeed(150);
	lbl->setMovie(movie);
	lbl->setAlignment(Qt::AlignCenter);
	movie->start();
	

	vbox->addWidget(lbl);
	setLayout(vbox);
}