#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include "qsdl/qsdlwidget.h"
#include "qsdl/qsdlexception.h"

class Widget : public QWidget
{
	Q_OBJECT
	QSdlWidget *w;
	QLabel *l = new QLabel("This is a normal Qt label =====================", this);

//	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
//	bool nativeEvent(const QByteArray &eventType, void *message, long *result){
//		qDebug() << "Event Entry";
//	}

public:
	Widget(QWidget *parent = 0, Qt::WindowFlags f = Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	~Widget();
};

#endif // WIDGET_H
