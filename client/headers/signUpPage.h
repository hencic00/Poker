#pragma once

#include <QFrame>

class signUpPage : public QFrame
{
	Q_OBJECT  

	public:
		signUpPage(QWidget *parent = 0);
		~signUpPage();

	private:
		void initUI();

	signals:
		void navigateTo(char* title, int index);

	public slots:
		void backButtonClicked();
		void applyButtonClicked();
};