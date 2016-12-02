#include "qsdlimage.h"


QSdlImage::QSdlImage(QSdlImage::QSdlImageFormat fmts, bool *ok) throw(QSdlException){
	setOk(false);
	try{
		if(!IMG_Init((int)fmts)){
			qDebug() << "QSdlImage: init image formats library failed: " << SDL_GetError();
			throw QSdlException("init image formats library failed");
		}
	}catch(...){
		setOk(false);
		throw;
	}

	setOk(true);
}

QSdlImage::~QSdlImage(){
	IMG_Quit();
}

QString QSdlImage::getVersion(){
	return QObject::tr("%1.%2.%3").arg(SDL_IMAGE_MAJOR_VERSION).arg(SDL_IMAGE_MINOR_VERSION).arg(SDL_IMAGE_PATCHLEVEL);
}
