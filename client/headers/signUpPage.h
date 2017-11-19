#pragma once

#include <QFrame>
#include <QLineEdit>

#include "connectionHandler/connectionHandler.h"

class signUpPage : public QFrame
{
	Q_OBJECT  

	public:
		signUpPage(QWidget *parent = 0);
		~signUpPage();

	private:
		void initUI();

		QLineEdit* email;
		QLineEdit* password;
		QLineEdit* passwordRe;

		connectionHandler* server;

	signals:
		void navigateTo(char* title, int index);

	public slots:
		void backButtonClicked();
		void applyButtonClicked();
};