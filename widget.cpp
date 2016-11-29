#include "widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	try{
		this->w = new QSdlWidget(QSdlWidget::Sdl_InitVideo, nullptr);

	}catch(QSdlException e){
		QMessageBox::critical(this, QApplication::applicationDisplayName(), e.getErrorString(), QMessageBox::Ok);
		return;
	}

	QGridLayout *lay = new QGridLayout;
	this->setLayout(lay);
	lay->addWidget(this->w, 0, 0, 1, 1);
	//lay->addWidget(this->l, 1, 0, 1, 1);

}

Widget::~Widget()
{

}
