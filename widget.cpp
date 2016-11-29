#include "widget.h"

Widget::Widget(QWidget *parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	try{
		this->w = new QSdlWidget(QSdlWidget::Sdl_InitVideo, this);

	}catch(QSdlException e){
		QMessageBox::critical(this, QApplication::applicationDisplayName(), e.getErrorString(), QMessageBox::Ok);
		return;
	}

	QGridLayout *lay = new QGridLayout;
	this->setLayout(lay);
	lay->addWidget(this->w, 0, 0, 1, 1);
	lay->addWidget(this->l, 1, 0, 1, 1);
	lay->setMargin(0);
	lay->setSizeConstraint(QLayout::SetFixedSize);

}

Widget::~Widget()
{

}
