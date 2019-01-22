#include "Blade.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Blade w;
	w.show();
	return a.exec();
}
