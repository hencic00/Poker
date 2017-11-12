#pragma once

#include <QFrame>
#include <QRect>
#include <QSvgRenderer>
#include <string>

class renderWidget : public QFrame
{

	Q_OBJECT

	public:
		renderWidget();
		~renderWidget();

		QString nekaj;
		QString* tableCards;

	private:
		int w;
		int h;



		void paintEvent(QPaintEvent *e);

};