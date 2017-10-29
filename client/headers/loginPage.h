#pragma once

#include <QFrame>

class loginPage : public QFrame
{
	Q_OBJECT  

	public:
		loginPage(QWidget *parent = 0);
		~loginPage();

		char* title;
		int index;

	private:
		void initUI();

	signals:
		void navigateTo(char* title, int index);

	public slots:
		void signUpButtonClicked();
		void loginButtonClicked();
};