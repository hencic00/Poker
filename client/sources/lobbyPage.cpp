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


#include "lobbyPage.h"

lobbyPage::lobbyPage(QWidget *parent):QFrame(parent)
{			 
	initUI();
}

lobbyPage::~lobbyPage()
{}

void lobbyPage::initUI(){}