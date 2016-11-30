#ifndef QSDLSURFACE_H
#define QSDLSURFACE_H

#include <QtCore>
#include "../global.h"
#include "SDL/SDL_video.h"
#include "qsdlpixelformat.h"

class QSdlSurface
{
	SDL_Surface surface;
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

	QSdlSurface(SDL_Surface surface){
		this->surface = surface;
	}

	SDL_Surface getSurface(){
		return this->surface;
	}

	SDL_Surface toSDL_Surface(){
		return this->surface;
	}
};

#endif // QSDLSURFACE_H
