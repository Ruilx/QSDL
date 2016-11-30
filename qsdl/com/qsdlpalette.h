#ifndef QSDLPALETTE_H
#define QSDLPALETTE_H

#include <QtCore>
#include <QColor>
#include "../global.h"
#include "../qsdlexception.h"
#include "SDL/SDL_video.h"

class QSdlPalette
{
	QList<QColor> colors;
public:
	QSdlPalette(QList<QColor> colors);
	QSdlPalette(int length = 0);
	QSdlPalette(SDL_Palette *palette);

	void addColor(QColor color);
	void addColor(int r, int g, int b);
	void setColor(int index, QColor color) throw(QSdlException);
	QColor getColor(int index) throw(QSdlException);

	SDL_Palette *toSDL_Palette();
};

#endif // QSDLPALETTE_H
