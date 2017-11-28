#pragma once

#include <QFrame>
#include <QLineEdit>
#include <QStackedWidget>
#include <QTimer>
#include <QLabel>

#include "connectionHandler/connectionHandler.h"

class loginPage : public QFrame
{
	Q_OBJECT  

	public:
		loginPage(QWidget *parent = 0);
		~loginPage();

		QLineEdit* emailInput;
		QLineEdit* passwordInput;

		connectionHandler* server;

		char* userName;
		char* userId;
		char* email;

		QLabel *alertLabel;

		char* title;
		int index;


		QTimer* timer;

		QStackedWidget* stack;

	private:
		void initUI();

	signals:
		void navigateTo(char* title, int index);

	public slots:
		void timeOut();
		void signUpButtonClicked();
		void loginButtonClicked();
};