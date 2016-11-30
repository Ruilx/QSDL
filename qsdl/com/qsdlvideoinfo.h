#ifndef SDLVIDEOINFO_H
#define SDLVIDEOINFO_H

#include <QtCore>
#include "qsdlpixelformat.h"
#include "SDL/SDL_video.h"

class QSdlVideoInfo
{
	bool hardwareAvailable;
	bool windowManagerAvailable;
	bool blockTransferHardware2Hardware;
	bool blockTransferHardware2HardwareWithColorKey;
	bool blockTransferHardware2HardwareWithAlpha;
	bool blockTransferSoftware2Hardware;
	bool blockTransferSoftware2HardwareWithColorKey;
	bool blockTransferSoftware2HardwareWithAlpha;
	bool blockTransferFill;
	qint32 videoMemoryKb;
	QSdlPixelFormat vFmt;
	QSize size;

public:
	QSdlVideoInfo();
	QSdlVideoInfo(SDL_VideoInfo info);
	SDL_VideoInfo toSDL_VideoInfo();

	bool isHardwareAvailable(){ return this->hardwareAvailable; }
	bool isWindowManagerAvailable(){ return this->windowManagerAvailable; }
	bool isBlockTransferHardware2Hardware(){ return this->blockTransferHardware2Hardware; }
	bool isBlockTransferHardware2HardwareWithColorKey(){ return this->blockTransferHardware2HardwareWithColorKey; }
	bool isBlockTransferHardware2HardwareWithAlpha(){ return this->blockTransferHardware2HardwareWithAlpha; }
	bool isBlockTransferSoftware2Hardware(){ return this->blockTransferSoftware2Hardware; }
	bool isBlockTransferSoftware2HardwareWithColorKey(){ return this->blockTransferSoftware2HardwareWithColorKey; }
	bool isBlockTransferSoftware2HardwareWithAlpha(){ return this->blockTransferSoftware2HardwareWithAlpha; }
	bool isBlockTransferFill(){ return this->blockTransferFill; }
	qint32 getVideoMemoryKb(){ return this->videoMemoryKb; }
	QSdlPixelFormat getVideoFormat(){ return this->vFmt; }
	QSize getSize(){ return this->size; }
};

#endif // SDLVIDEOINFO_H
