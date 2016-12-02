#include "widget.h"

Widget::Widget(QWidget *parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	try{
		this->w = new QSdlWidget(QSdlWidget::Sdl_InitEverything, this);

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

	//this->setMouseTracking(true);

	try{
		if(!this->w->setupSurface(640, 480, QSdlSurface::Sdl_32Bits, (QSdlSurface::SdlSurfaceFlags)(QSdlSurface::Sdl_SwSurface | QSdlSurface::Sdl_DoubleBuf))){
			throw QString("Error");
		}

		QSdlSurface *surface = new QSdlSurface();
		if(!surface->loadImage("data/background/title.bmp")){
			throw QString("Error2");
		}

		if(!this->w->blitSurface(surface)){
			throw QString("Error3");
		}

		if(!this->w->update()){
			throw QString("Error4");
		}
	}catch(QString str){
		qDebug() << str << ":" << SDL_GetError();
		return;
	}


}

Widget::~Widget()
{

}
