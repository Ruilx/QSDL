#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "qsdl/qsdlwidget.h"
#include "qsdl/qsdlexception.h"

class Widget : public QWidget
{
	Q_OBJECT
	QSdlWidget *w;
	QLabel *l = new QLabel("The Widget Above, is a SDL widget ^_^", this);

public:
	Widget(QWidget *parent = 0, Qt::WindowFlags f = Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	~Widget();
};

#endif // WIDGET_H
