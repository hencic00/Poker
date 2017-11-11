#pragma once

#include <QFrame>

class lobbyPage : public QFrame
{
	Q_OBJECT  

	public:
		lobbyPage(QWidget *parent = 0);
		~lobbyPage();

		char* title;
		int index;

	private:
		void initUI();
};