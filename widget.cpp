#include "widget.h"

//void Widget::keyPressEvent(QKeyEvent *event)
//{
//	Qt::KeyboardModifiers modifier = event->modifiers();
//	int key = event->key();
//	QString keyStr = event->text();
//	switch(key){
//		case Qt::Key_Escape:
//			qDebug() << "You Pressed Escape key!";
//		default:
//			qDebug() << "You Pressed key value is MOD:" << modifier << "KEY:" << key << "STR:" << keyStr;
//	}

//	QWidget::keyPressEvent(event);
//}

void Widget::mousePressEvent(QMouseEvent *event)
{
	Qt::MouseButtons buttons = event->buttons();
	QString str = "You Pressed Mouse: ";
	if(buttons & Qt::LeftButton){
		str.append("Left ");
	}
	if(buttons & Qt::RightButton){
		str.append("Right ");
	}
	if(buttons & Qt::MidButton){
		str.append("Mid ");
	}
	if(buttons & Qt::BackButton){
		str.append("Back ");
	}
	if(buttons & Qt::ForwardButton){
		str.append("Forward ");
	}
	str.append(tr("at (%1, %2)").arg(event->x()).arg(event->y()));

	qDebug() << str;

	QWidget::mousePressEvent(event);
}

Widget::Widget(QWidget *parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	try{
		this->w = new QSdlWidget(QSdlWidget::Sdl_InitVideo, this);

	}catch(QSdlException e){
		QMessageBox::critical(this, QApplication::applicationDisplayName(), e.getErrorString(), QMessageBox::Ok);
		return;
	}

	this->l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QGridLayout *lay = new QGridLayout;
	this->setLayout(lay);
	lay->addWidget(this->w, 0, 0, 1, 1);
	lay->addWidget(this->l, 1, 0, 1, 1);
	lay->setMargin(0);
	//lay->setSizeConstraint(QLayout::SetFixedSize);

}

Widget::~Widget()
{

}
