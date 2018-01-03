#pragma once

#include <QFrame>
#include <QRect>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include "renderWidget.h"
#include "connectionHandler/serverHandler.h"
#include <string>

class playPage : public QFrame
{
	Q_OBJECT  

	public:
		playPage(QWidget *parent = 0);
		~playPage();
		int nmOfPlayers;
		renderWidget* render;
		void draw(int nmOfPlayers, QString* userNames, int* userSid, int mySid);
		serverHandler* server;
		void stackFocus();
		QThread* thread1;
		std::map<std::string, QString> card;
		QPushButton* raiseButton;
		QPushButton* checkButton;
		QPushButton* foldButton;
		QSlider* bettAmmoutScroll;
		QLabel* bettAmmout;
		int prevBet;
		int bigBlind;
		int minBet;

	private:
		void initUI();

		// std::string nekaj;

		QString tableCards[5];
		int nekaj;
		
	
	public slots:
		void raiseButtonClicked();
		void checkButtonClicked();
		void foldButtonClicked();
		void betAmmountSlider(int value);
};