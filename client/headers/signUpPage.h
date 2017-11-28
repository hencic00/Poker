#pragma once

#include <QFrame>
#include <QLineEdit>
#include <QLabel>

#include "connectionHandler/connectionHandler.h"
#include "userData.h"

class signUpPage : public QFrame
{
	Q_OBJECT  

	public:
		signUpPage(QWidget *parent = 0);
		~signUpPage();
		connectionHandler* server;

		char* userName;
		char* userId;
		char* email;


	private:
		void initUI();

		QLineEdit* emailInput;
		QLineEdit* userNameInput;
		QLineEdit* passwordInput;
		QLineEdit* passwordRe;

		QLabel *alertLabel;



	signals:
		void navigateTo(char* title, int index);
		void serverRequest(char* agenda, char* args, int argc);

	public slots:
		void backButtonClicked();
		void applyButtonClicked();
};