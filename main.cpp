#include <QApplication>
#include <iostream>

#include "otto.h"

class Otto;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Otto *ottoDialog = new Otto;
	ottoDialog->show();

	return app.exec();
}
