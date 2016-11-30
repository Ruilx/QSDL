#include "qsdlvideoinfo.h"

QSdlVideoInfo::QSdlVideoInfo(): QSdlVideoInfo(*SDL_GetVideoInfo())
{

}

QSdlVideoInfo::QSdlVideoInfo(SDL_VideoInfo info){
	this->hardwareAvailable = info.hw_available > 0? true: false;
	this->windowManagerAvailable = info.wm_available > 0? true: false;
	this->blockTransferHardware2Hardware = info.blit_hw > 0? true: false;
	this->blockTransferHardware2HardwareWithColorKey = info.blit_hw_CC > 0? true: false;
	this->blockTransferHardware2HardwareWithAlpha = info.blit_hw_A > 0? true: false;
	this->blockTransferSoftware2Hardware = info.blit_sw > 0? true: false;
	this->blockTransferSoftware2HardwareWithColorKey = info.blit_sw_CC > 0? true: false;
	this->blockTransferSoftware2HardwareWithAlpha = info.blit_sw_A > 0? true: false;
	this->blockTransferFill = info.blit_fill > 0? true: false;
	this->videoMemoryKb = info.video_mem;
	this->vFmt = QSdlPixelFormat(info.vfmt);
}

SDL_VideoInfo QSdlVideoInfo::toSDL_VideoInfo(){
	SDL_VideoInfo info;
	info.hw_available = this->hardwareAvailable? 1: 0;
	info.wm_available = this->windowManagerAvailable? 1: 0;
	info.blit_hw = this->blockTransferHardware2Hardware? 1: 0;
	info.blit_hw_CC = this->blockTransferHardware2HardwareWithColorKey? 1: 0;
	info.blit_hw_A = this->blockTransferHardware2HardwareWithAlpha? 1: 0;
	info.blit_sw = this->blockTransferSoftware2Hardware? 1: 0;
	info.blit_sw_CC = this->blockTransferSoftware2HardwareWithColorKey? 1: 0;
	info.blit_sw_A = this->blockTransferSoftware2HardwareWithAlpha? 1: 0;
	info.blit_fill = this->blockTransferFill? 1: 0;
	info.video_mem = this->videoMemoryKb;
	info.vfmt = this->vFmt.toSDL_PixelFormat();
	info.current_h = this->size.width();
	info.current_w = this->size.height();
	return info;
}
