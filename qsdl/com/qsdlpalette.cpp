#include "qsdlpalette.h"

QSdlPalette::QSdlPalette(QList<QColor> colors){
	for(QColor color: colors){
		this->colors.append(color);
	}
}

QSdlPalette::QSdlPalette(int length){
	if(length == 0){
		return;
	}else{
		for(int i = 0; i < length; i++){
			this->colors.append(QColor());
		}
	}
}

QSdlPalette::QSdlPalette(SDL_Palette *palette){
	if(palette->ncolors == 0){
		return;
	}else{
		for(int i = 0; i < palette->ncolors; i++){
			this->colors.append(QColor(palette->colors[i].r, palette->colors[i].g, palette->colors[i].b));
		}
	}
}

void QSdlPalette::addColor(QColor color){
	this->colors.append(color);
}

void QSdlPalette::addColor(int r, int g, int b){
	this->colors.append(QColor(r, g, b));
}

void QSdlPalette::setColor(int index, QColor color) throw(QSdlException) {
	try{
		if(index >= this->colors.length()){
			throw QSdlException(QObject::tr("setColor: index(%1) out of length(%2).").arg(index).arg(this->colors.length()));
		}else{
			this->colors[index] = color;
		}
	}catch(...){
		throw;
	}
}

QColor QSdlPalette::getColor(int index) throw(QSdlException) {
	try{
		if(index >= this->colors.length()){
			throw QSdlException(QObject::tr("getColor: index(%1) out of length(%2).").arg(index).arg(this->colors.length()));
		}else{
			return this->colors.at(index);
		}
	}catch(...){
		throw;
	}
}

SDL_Palette *QSdlPalette::toSDL_Palette(){
	SDL_Palette *p = new SDL_Palette;
	int length = this->colors.length();
	SDL_Color *c = new SDL_Color[length];
	for(int i = 0; i < length; i++){
		int r, g, b;
		this->colors.at(i).getRgb(&r, &g, &b);
		c[i].r = (uint)r;
		c[i].g = (uint)g;
		c[i].b = (uint)b;
	}
	p->ncolors = length;
	p->colors = c;
	return p;
}
