#include "widget.h"
#include <QApplication>
#include "qsdl/qsdlwidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.show();

//	QSdlWidget w(QSdlWidget::Sdl_InitVideo, nullptr, Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
//	w.show();

	return a.exec();
}
