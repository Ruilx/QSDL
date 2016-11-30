#ifndef QSDLVIDEO_H
#define QSDLVIDEO_H

#include <SDL/SDL.h>
#include "qsdlexception.h"
#include "global.h"
#include "com/qsdlsurface.h"
#include "com/qsdlvideoinfo.h"

class QSdlVideo
{
public:
	enum SdlVideoMode{

	};

	QSdlVideo();

	static QString getSdlVideoDriverName();
};

#endif // QSDLVIDEO_H
