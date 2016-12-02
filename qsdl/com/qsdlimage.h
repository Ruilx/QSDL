#ifndef QSDLIMAGE_H
#define QSDLIMAGE_H

#include <QtCore>
#include <SDL/SDL_image.h>
#include "qsdlsurface.h"
#include "../qsdlexception.h"
#include "../global.h"

class QSdlImage: public QSdlSurface
{

public:
	enum QSdlImageFormat{
		QSdl_Jpg = IMG_INIT_JPG,
		QSdl_Png = IMG_INIT_PNG,
		QSdl_Tif = IMG_INIT_TIF,
		QSdl_Webp = IMG_INIT_WEBP,
		QSdl_ImgAll = QSdl_Jpg | QSdl_Png | QSdl_Tif | QSdl_Webp,
		QSdl_ImgCommon = QSdl_Jpg | QSdl_Png
	};

	QSdlImage(QSdlImageFormat fmts = QSdl_ImgCommon, bool *ok = nullptr) throw(QSdlException);

	~QSdlImage();

	bool loadImage(QString filename){
		this->setSurface(IMG_Load(filename.toLocal8Bit().data()));
		if(this->getSurface() == nullptr){
			return false;
		}else{
			SDL_SetColorKey(this->getSurface(), SDL_RLEACCEL, this->getSurface()->format->colorkey);
			return true;
		}
	}

	static QString getVersion();
};

#endif // QSDLIMAGE_H
