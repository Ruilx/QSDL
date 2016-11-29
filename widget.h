#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "qsdl/qsdlwidget.h"
#include "qsdl/qsdlexception.h"

class Widget : public QWidget
{
	Q_OBJECT
	QSdlWidget *w;
	//QLabel *l = new QLabel("123", this);
public:
	Widget(QWidget *parent = 0);
	~Widget();
};

#endif // WIDGET_H
