#include "qsdlpixelformat.h"

QSdlPixelFormat::QSdlPixelFormat(QSdlPalette &palette, quint8 bitsPerPixel, quint8 bytesPerPixel, quint8 redLoss, quint8 greenLoss, quint8 blueLoss, quint8 alphaLoss, quint8 redShift, quint8 greenShift, quint8 blueShift, quint8 alphaShift, quint32 redMask, quint32 greenMask, quint32 blueMask, quint32 alphaMask, quint32 colorKey, quint32 alpha){
	this->palette = palette;
	this->bitsPerPixel = bitsPerPixel;
	this->bytesPerPixel = bytesPerPixel;
	this->redLoss = redLoss;
	this->greenLoss = greenLoss;
	this->blueLoss = blueLoss;
	this->alphaLoss = alphaLoss;
	this->redShift = redShift;
	this->greenShift = greenShift;
	this->blueShift = blueShift;
	this->alphaShift = alphaShift;
	this->redMask = redMask;
	this->greenMask = greenMask;
	this->blueMask = blueMask;
	this->alphaMask = alphaMask;
	this->colorKey = colorKey;
	this->alpha = alpha;
}

QSdlPixelFormat::QSdlPixelFormat(){

}

QSdlPixelFormat::QSdlPixelFormat(SDL_PixelFormat *format){
	this->palette = QSdlPalette(format->palette);
	this->bitsPerPixel = format->BitsPerPixel;
	this->bytesPerPixel = format->BytesPerPixel;
	this->redLoss = format->Rloss;
	this->greenLoss = format->Gloss;
	this->blueLoss = format->Bloss;
	this->alphaLoss = format->Aloss;
	this->redShift = format->Rshift;
	this->greenShift = format->Gshift;
	this->blueShift = format->Bshift;
	this->alphaShift = format->Ashift;
	this->redMask = format->Rmask;
	this->greenMask = format->Gmask;
	this->blueMask = format->Bshift;
	this->alphaMask = format->Amask;
	this->colorKey = format->colorkey;
	this->alpha = format->alpha;
}

SDL_PixelFormat *QSdlPixelFormat::toSDL_PixelFormat(){
	SDL_PixelFormat *f = new SDL_PixelFormat;
	f->palette = this->palette.toSDL_Palette();
	f->BitsPerPixel = this->bitsPerPixel;
	f->BytesPerPixel = this->bytesPerPixel;
	f->Rloss = this->redLoss;
	f->Gloss = this->greenLoss;
	f->Bloss = this->blueLoss;
	f->Aloss = this->alphaLoss;
	f->Rshift = this->redShift;
	f->Gshift = this->greenShift;
	f->Bshift = this->blueShift;
	f->Ashift = this->alphaShift;
	f->Rmask = this->redMask;
	f->Gmask = this->greenMask;
	f->Bmask = this->blueMask;
	f->Amask = this->alphaMask;
	f->colorkey = this->colorKey;
	f->alpha = this->alpha;
	return f;
}
