#include "qsdlvideo.h"

QSdlVideo::QSdlVideo()
{

}

QString QSdlVideo::getSdlVideoDriverName(){
	char a[128];
	char *b = SDL_VideoDriverName(a, 128);
	if(b != nullptr){
		return QString(a);
	}else{
		return QString();
	}
}
