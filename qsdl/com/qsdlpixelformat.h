#ifndef QSDLPIXELFORMAT_H
#define QSDLPIXELFORMAT_H

#include <QtCore>
#include "qsdlpalette.h"
#include "SDL/SDL_video.h"

/* Everything in the pixel format structure is Read-Only */

class QSdlPixelFormat
{
	QSdlPalette palette;
	quint8 bitsPerPixel;
	quint8 bytesPerPixel;
	quint8 redLoss;
	quint8 greenLoss;
	quint8 blueLoss;
	quint8 alphaLoss;
	quint8 redShift;
	quint8 greenShift;
	quint8 blueShift;
	quint8 alphaShift;
	quint32 redMask;
	quint32 greenMask;
	quint32 blueMask;
	quint32 alphaMask;
	/* RGB color key information */
	quint32 colorKey;
	/* Alpha value information (per-surface alpha) */
	quint8 alpha;
public:

protected:
	QSdlPixelFormat(QSdlPalette &palette,
					quint8 bitsPerPixel,
					quint8 bytesPerPixel,
					quint8 redLoss,
					quint8 greenLoss,
					quint8 blueLoss,
					quint8 alphaLoss,
					quint8 redShift,
					quint8 greenShift,
					quint8 blueShift,
					quint8 alphaShift,
					quint32 redMask,
					quint32 greenMask,
					quint32 blueMask,
					quint32 alphaMask,
					quint32 colorKey,
					quint32 alpha);
public:
	QSdlPixelFormat();
	QSdlPixelFormat(SDL_PixelFormat *format);

	SDL_PixelFormat *toSDL_PixelFormat();
};

#endif // QSDLPIXELFORMAT_H
