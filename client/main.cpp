#include <QApplication>

#include "pokerWindow.h"

int main(int argc, char *argv[]) 
{ 
	QApplication app(argc, argv);
	
	pokerWindow window;
	window.show();

	return app.exec();
}