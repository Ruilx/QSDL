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
	this->s->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	this->s->setRange(0, 128);
	this->s->setTickInterval(1);
	this->s->setValue(128);

	connect(this->s, &QSlider::valueChanged, this, [this](int value){
		this->w->bgm()->setVolume(value);
	});

	QGridLayout *lay = new QGridLayout;
	this->setLayout(lay);
	lay->addWidget(this->w, 0, 0, 1, 1, Qt::AlignCenter);
	lay->addWidget(this->l, 1, 0, 1, 1);
	lay->addWidget(this->s, 2, 0, 1, 1);
	lay->setMargin(0);
	//lay->setSizeConstraint(QLayout::SetFixedSize);

	//this->setMouseTracking(true);

	try{
		if(!this->w->setupSurface(640, 480, QSdlSurface::Sdl_32Bits, (QSdlSurface::SdlSurfaceFlags)(QSdlSurface::Sdl_SwSurface | QSdlSurface::Sdl_DoubleBuf))){
			throw QString("Error setupSurface");
		}

//		QSdlSurface *surface = new QSdlSurface();
//		if(!surface->loadImage("data/background/title.bmp")){
//			throw QString("Error loadImage");
//		}
		bool ok = false;
		QSdlImage *surface = new QSdlImage(QSdlImage::QSdl_ImgCommon, &ok);
		if(ok == false){
			throw QString("Error QSdlImage");
		}else{
			if(!surface->loadImage("data/background/title.png")){
				throw QString("Error loadImage");
			}
		}

		if(!this->w->blitSurface(surface)){
			throw QString("Error blitSurface");
		}

		if(!this->w->update()){
			throw QString("Error update");
		}

		w->bgm()->setMusic(tr("data/bgm/title.mid"));
		if(!w->bgm()->play(QSdlMixer::SdlPlayInifinitely)){
			throw QString("Error play");
		}
		w->bgm()->setVolume(128);

		QSdlFontImage *font = new QSdlFontImage("data/fonts/msyh.ttc", 20, this);
		this->w->blitSurface(font->toSurfaceAlpha("Hello, world", QSdlColor(255, 255, 255)), QPoint(50, 50));
		delete font;

		if(!this->w->update()){
			throw QString("Error update");
		}


//		QSdlSound *s = new QSdlSound(QSdlMixer::Sdl_InitCommon, this);
//		s->setSound(tr("data/bgm/title.ogg"));
//		if(!s->play()){
//			throw QString("Error Sound");
//		}
//		s->setVolume(128);



//		QMediaPlayer *player = new QMediaPlayer(this);
//		player->setMedia(QUrl("data/bgm/title.mp3"));
//		player->setVolume(100);
//		player->play();


	}catch(QString str){
		qDebug() << str << ":" << SDL_GetError();
		return;
	}catch(QSdlException ex){
		qDebug() << "Error: " << ex.getErrorString();
	}

	//this->sound->setLoops(QSound::Infinite);
	//this->sound->play();

}

Widget::~Widget()
{

}
