#pragma once

#include <QFrame>

class loadingPage : public QFrame
{
	Q_OBJECT  

	public:
		loadingPage(QWidget *parent = 0);
		~loadingPage();

	private:
		void initUI();

	signals:
		void navigateTo(char* title, int index);
};