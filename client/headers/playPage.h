#pragma once

#include <QFrame>
#include <QRect>

class playPage : public QFrame
{
	Q_OBJECT  

	public:
		playPage(QWidget *parent = 0);
		~playPage();

	private:
		void initUI();

		// std::string nekaj;
		
	
	public slots:
		void raiseButtonClicked();
};