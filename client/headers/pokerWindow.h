#pragma once

#include <QFrame>
#include <QStyle>
#include <QStackedWidget>
#include <string>

class pokerWindow : public QFrame
{
	Q_OBJECT  

	public:
		pokerWindow(QWidget *parent = 0);
		~pokerWindow();

	private:
		void initUI();
		void setWindowGeometry();

		QStackedWidget* stack;

	public slots:
		void navigationRequestReceived(char* title, int index);
};