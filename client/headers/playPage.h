#pragma once

#include <QFrame>
#include <QRect>
#include "renderWidget.h"
#include <string>

class playPage : public QFrame
{
	Q_OBJECT  

	public:
		playPage(QWidget *parent = 0);
		~playPage();

	private:
		void initUI();

		// std::string nekaj;
		renderWidget* render;
		std::map<std::string, QString> card;

		QString tableCards[5];
		int nekaj;
		
	
	public slots:
		void raiseButtonClicked();
};