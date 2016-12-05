#ifndef QSDLSURFACE_H
#define QSDLSURFACE_H

#include <QtCore>
#include <QWidget>
#include "../global.h"
#include "SDL/SDL_video.h"
#include "qsdlpixelformat.h"

class QSdlSurface
{
	SDL_Surface *surface = nullptr;
	QWidget *parent = nullptr;
public:
	enum SdlSurfaceFlags{
		Sdl_SwSurface = SDL_SWSURFACE,
		Sdl_HwSurface = SDL_HWSURFACE,
		Sdl_AsyncBlit = SDL_ASYNCBLIT,
		Sdl_AnyFormat = SDL_ANYFORMAT,
		Sdl_HwPalette = SDL_HWPALETTE,
		Sdl_DoubleBuf = SDL_DOUBLEBUF,
		Sdl_Fullscreen = SDL_FULLSCREEN,
		Sdl_Opengl = SDL_OPENGL,
		Sdl_OpenglBlit = SDL_OPENGLBLIT,
		Sdl_Resizable = SDL_RESIZABLE,
		Sdl_NoFrame = SDL_NOFRAME,
		Sdl_HwAccel = SDL_HWACCEL,
		Sdl_SrcColorKey = SDL_SRCCOLORKEY,
		Sdl_RleAccelOk = SDL_RLEACCELOK,
		Sdl_RleAccel = SDL_RLEACCEL,
		Sdl_SrcAlpha = SDL_SRCALPHA,
		Sdl_PreAlloc = SDL_PREALLOC
	};

	enum SdlSurfaceScreenBpp{
		Sdl_8bits = 8,
		Sdl_9bits = 9,
		Sdl_12bits = 12,
		Sdl_16bits = 16,
		Sdl_24bits = 24,
		Sdl_32Bits = 32
	};

protected:

	void setSurface(SDL_Surface *surface){
		this->surface = surface;
	}

	void setSurface(SDL_Surface surface){
		if(this->surface == nullptr){
			this->surface = new SDL_Surface;
		}
		*(this->surface) = surface;

	}

	void freeSurface(){
		if(this->surface != nullptr){
			SDL_FreeSurface(this->surface);
			this->surface = nullptr;
		}
	}

public:
	QSdlSurface(SDL_Surface *surface){
		this->surface = surface;
	}

	QSdlSurface(){
		this->surface = nullptr;
	}

	~QSdlSurface(){
		if(this->surface != nullptr){
			SDL_FreeSurface(this->surface);
		}
	}

	SDL_Surface *getSurface(){
		return this->surface;
	}

	SDL_Surface *toSDL_Surface(){
		return this->surface;
	}

	bool isNull(){ return (this->surface == nullptr); }

	QSdlSurface(const QSize &screenSize, SdlSurfaceScreenBpp bpp, SdlSurfaceFlags flags = Sdl_SwSurface, QWidget *parent = nullptr, bool *ok = nullptr){
		setOk(false);
		this->surface = SDL_SetVideoMode( screenSize.width(), screenSize.height(), (int)bpp, (quint32)flags);
		if(this->surface == nullptr){
			setOk(false);
			qDebug() << "QSdlSurface surface setup failed: " << SDL_GetError();
			return;
		}
		if(parent != nullptr){
			this->parent = parent;
			if((flags & Sdl_Resizable) == 0){
				parent->setFixedSize(screenSize.width(), screenSize.height());
			}
		}
	}

	QSdlSurface(int width, int height, SdlSurfaceScreenBpp bpp, SdlSurfaceFlags flags = Sdl_SwSurface, QWidget *parent = nullptr, bool *ok = nullptr){
		setOk(false);
		this->surface = SDL_SetVideoMode( width, height, (int)bpp, (quint32)flags);
		if(this->surface == nullptr){
			setOk(false);
			qDebug() << "QSdlSurface surface setup failed: " << SDL_GetError();
			return;
		}
		setOk(true);
		if(parent != nullptr){
			this->parent = parent;
			if((flags & Sdl_Resizable) == 0){
				parent->setFixedSize(width, height);
			}
		}
	}

	QSdlSurface *toDisplayFormat(QSdlSurface *sourceImage, bool destroySourceImage = false){
		QSdlSurface *dest = new QSdlSurface(SDL_DisplayFormat(sourceImage->toSDL_Surface()));
		if(destroySourceImage == true){
			delete sourceImage;
			sourceImage = nullptr;
		}
		return dest;
	}

	void convertSurfaceToDisplayFormat(){
		QSdlSurface *dest = new QSdlSurface(SDL_DisplayFormat(this->surface));
		this->freeSurface();
		SDL_Surface sdlDest = *(dest->toSDL_Surface());
		this->setSurface(sdlDest);
	}

	bool blitSurface(QSdlSurface *surface, const QPoint &loc = QPoint(0, 0), const QRect &croppingArea = QRect()){
		SDL_Rect offset;
		offset.x = loc.x();
		offset.y = loc.y();
		if(!croppingArea.isNull()){
			SDL_Rect croppingOffset;
			croppingOffset.x = croppingArea.left();
			croppingOffset.y = croppingArea.top();
			croppingOffset.w = croppingArea.width();
			croppingOffset.h = croppingArea.height();
			if(SDL_UpperBlit(surface->toSDL_Surface(), &croppingOffset, this->surface, &offset) < 0){
				return false;
			}else{
				return true;
			}
		}else{
			if(SDL_UpperBlit(surface->toSDL_Surface(), nullptr, this->surface, &offset) <0){
				return false;
			}else{
				return true;
			}
		}
	}

	bool loadImage(QString filename, bool autoConvert = true){
		this->surface = SDL_LoadBMP_RW(SDL_RWFromFile(filename.toLocal8Bit().data(), "rb"), 1);
		if(this->surface == nullptr){
			return false;
		}else{
			if(autoConvert == true){
				this->convertSurfaceToDisplayFormat();
			}
			return true;
		}
	}

	bool updateSurface(){
		if(this->surface != nullptr){
			int r = SDL_Flip(this->surface);
			if(r < 0){
				return false;
			}else{
				return true;
			}
		}else{
			SDL_SetError("Surface is empty.");
			return false;
		}
	}
};

#endif // QSDLSURFACE_H
