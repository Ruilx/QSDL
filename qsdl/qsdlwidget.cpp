#include "qsdlwidget.h"

#define setOk(v) if(ok){ *ok = (v); }

QSdlWidget::QSdlWidget(QSdlWidget::QSdlInitDevices devices, QWidget *parent, Qt::WindowFlags flags, bool *ok) throw(QSdlException): QWidget(nullptr, flags), parent(parent)
{
	setOk(false);

	this->setAttribute(Qt::WA_PaintOnScreen, true);
	this->setUpdatesEnabled(false);

	this->SetVideoSdlWindowId(this->winId());

	try{
		if(SDL_Init(devices)< 0){
			setOk(false);
			throw QSdlException("SDL_Init() failed: {$sdl_error}.");
		}

	}catch(...){
		throw;
	}

	this->mainSurface = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE | SDL_DOUBLEBUF);
	//this->resize(SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h);
	this->setFixedSize(SDL_GetVideoInfo()->current_w, SDL_GetVideoInfo()->current_h);

	SDL_Surface *s = SDL_LoadBMP(QString(QDir::currentPath() + "/data/background/bg.bmp").toLocal8Bit().data());

	SDL_BlitSurface(s, nullptr, this->mainSurface, nullptr);
	SDL_Flip(s);

	setOk(true);

	QThread *sdlEventThread = new QThread(this);
	this->sdlEvent->moveToThread(sdlEventThread);
	connect(sdlEventThread, SIGNAL(started()), this->sdlEvent, SLOT(listenSdlEvent()));
	connect(sdlEventThread, SIGNAL(finished()), this->sdlEvent, SLOT(deleteLater()));
	connect(this->sdlEvent, SIGNAL(sdlQuitSig()), sdlEventThread, SLOT(quit()));
	connect(this->sdlEvent, SIGNAL(sdlShowHideSig(bool)), this, SLOT(sdlEventShowHideSlot(bool)));
	connect(this->sdlEvent, SIGNAL(sdlKeySig(QEvent::Type,Qt::Key,Qt::KeyboardModifiers,QString)), this, SLOT(sdlEventKeySigSlot(QEvent::Type,Qt::Key,Qt::KeyboardModifiers,QString)));
	sdlEventThread->start();

}

QSdlWidget::QSdlWidget(QWidget *parent, Qt::WindowFlags flags, bool *ok)throw(QSdlException) : QWidget(nullptr, flags), parent(parent)
{
	setOk(false);

	this->setAttribute(Qt::WA_PaintOnScreen, true);
	this->setUpdatesEnabled(false);

	if(parent != nullptr && this->winId() != (int)nullptr){
		this->SetVideoSdlWindowId(this->winId());
	}

	setOk(true);

	this->qKeyMap = new QSdlKeyboardMap();
}

bool QSdlWidget::initSubSystem(QSdlWidget::QSdlInitDevices devices) throw(QSdlException)
{
	try{
		if(SDL_InitSubSystem(devices) < 0){
			throw QSdlException("SDL_InitSubSystem() failed: {$sdl_error}.");
			return false;
		}
	}catch(...){
		throw;
	}

	return true;
}

QSdlWidget::QSdlInitDevices QSdlWidget::isInit(QSdlWidget::QSdlInitDevices devices)
{
	return (QSdlInitDevices)SDL_WasInit(devices);
}

void QSdlWidget::quitSubSystem(QSdlWidget::QSdlInitDevices devices) Q_DECL_NOTHROW
{
	SDL_QuitSubSystem(devices);
}

void QSdlWidget::quit() Q_DECL_NOTHROW
{
	SDL_Quit();
}

void QSdlWidget::setToEnvironment(QString name, QString value)
{
	qDebug() << tr("[Environment]: %1=%2").arg(name).arg(value);
	SDL_putenv(QString(name + "=" + value).toLocal8Bit().data());
}

QString QSdlWidget::getVideoDriverNameInTheList(QSdlWidget::QSdlVideoDriver driver)
{
	switch(driver){
		case Sdl_Quartz: return QString("Quartz");
		case Sdl_X11: return QString("x11");
		case Sdl_Dga: return QString("dga");
		case Sdl_Nanox: return QString("nanox");
		case Sdl_Ipod: return QString("ipod");
		case Sdl_Qtopia: return QString("qtopia");
		case Sdl_Wscons: return QString("wscons");
		case Sdl_Fbcon: return QString("fbcon");
		case Sdl_DirectFb: return QString("directfb");
		case Sdl_Ps2gs: return QString("ps2gs");
		case Sdl_Ggi: return QString("ggi");
		case Sdl_Vgl: return QString("vgl");
		case Sdl_Svgalib: return QString("svgalib");
		case Sdl_Gapi: return QString("gapi");
		case Sdl_Windib: return QString("windib");
		case Sdl_Directx: return QString("directx");
		case Sdl_Bwindow: return QString("bwindow");
		case Sdl_Toolbox: return QString("toolbox");
		case Sdl_Dspvideo: return QString("DSp");
		case Sdl_Photon: return QString("photon");
		case Sdl_Epocvideo: return QString("epoc");
		case Sdl_Xbios: return QString("xbios");
		case Sdl_Gem: return QString("gem");
		case Sdl_Picogui: return QString("picogui");
		case Sdl_Dcvideo: return QString("dcvideo");
		case Sdl_Ndsvideo: return QString("nds");
		case Sdl_Riscos: return QString("riscos");
		case Sdl_Os2fslib: return QString("os2fslib");
		case Sdl_Aalib: return QString("aalib");
		case Sdl_Dummyvideo: return QString("dummy");
		default: return QString("dummy");
	}
}

QString QSdlWidget::getAudioDriverNameInTheList(QSdlWidget::QSdlAudioDriver driver)
{
	switch(driver){
		case Sdl_Openbsd: return QString("openbsd");
		case Sdl_Dspaudio: return QString("dsp");
		case Sdl_Dma: return QString("dma");
		case Sdl_Alsa: return QString("alsa");
		case Sdl_Pulse: return QString("pulse");
		case Sdl_Qsanto: return QString("qsa-nto");
		case Sdl_Audio: return QString("audio");
		case Sdl_Al: return QString("AL");
		case Sdl_Artsc: return QString("artsc");
		case Sdl_Esd: return QString("esd");
		case Sdl_Nas: return QString("nas");
		case Sdl_Dsound: return QString("dsound");
		case Sdl_Waveout: return QString("waveout");
		case Sdl_Paud: return QString("paud");
		case Sdl_Baudio: return QString("baudio");
		case Sdl_Coreaudio: return QString("coreaudio");
		case Sdl_Sndmgr: return QString("sndmgr");
		case Sdl_Mint_gsxb: return QString("mint_gsxb");
		case Sdl_Mint_mcsn: return QString("mint_mcsn");
		case Sdl_Mint_stfa: return QString("mint_stfa");
		case Sdl_Mint_xbios: return QString("mint_xbios");
		case Sdl_Mint_dma8: return QString("mint_dma8");
		case Sdl_Disk: return QString("disk");
		case Sdl_Dummyaudio: return QString("dummy");
		case Sdl_DcAudio: return QString("dcaudio");
		case Sdl_Ndsaudio: return QString("nds");
		case Sdl_Waveout2: return QString("waveout");
		case Sdl_Dart: return QString("dart");
		case Sdl_Epocaudio: return QString("epoc");
		default: return QString("dummy");
	}
}

QString QSdlWidget::getEnvironmentNameInTheList(QSdlWidget::QSdlEnvironment env)
{
	switch(env){
		case Sdl_FbAccel: return QString("SDL_FBACCEL");
		case Sdl_FbDev: return QString("SDL_FBDEV");
		case Sdl_FullscreenUpdate: return QString("SDL_FULLSCREEN_UPDATE");
		case Sdl_VideoDriver: return QString("SDL_VIDEODRIVER");
		case Sdl_VideoCentered: return QString("SDL_VIDEO_CENTERED");
		case Sdl_VideoWindowPos: return QString("SDL_VIDEO_WINDOW_POS");
		case Sdl_VideoGlDriver: return QString("SDL_VIDEO_GL_DRIVER");
		case Sdl_X11DgaMouse: return QString("SDL_VIDEO_X11_DGAMOUSE");
		case Sdl_X11MouseAccel: return QString("SDL_VIDEO_X11_MOUSEACCEL");
		case Sdl_VideoX11NoDirectColor: return QString("SDL_VIDEO_X11_NODIRECTCOLOR");
		case Sdl_VideoX11VisualId: return QString("SDL_VIDEO_X11_VISUALID");
		case Sdl_VideoX11WmcClass: return QString("SDL_VIDEO_X11_WMCLASS");
		case Sdl_VideoYuvDirect: return QString("SDL_VIDEO_YUV_DIRECT");
		case Sdl_VideoYuvHwAccel: return QString("SDL_VIDEO_YUV_HWACCEL");
		case Sdl_WindowId: return QString("SDL_WINDOWID");
		case Sdl_MouseRelative: return QString("SDL_MOUSE_RELATIVE");
		case Sdl_MouseDev: return QString("SDL_MOUSEDEV");
		case Sdl_MouseDevImps2: return QString("SDL_MOUSEDEV_IMPS2");
		case Sdl_MouseDrv: return QString("SDL_MOUSEDRV");
		case Sdl_NoRawKeyboard: return QString("SDL_NO_RAWKBD");
		case Sdl_NoMouse: return QString("SDL_NOMOUSE");
		case Sdl_AudioDev: return QString("AUDIODEV");
		case Sdl_AudioDriver: return QString("SDL_AUDIODRIVER");
		case Sdl_DiskAudioFile: return QString("SDL_DISKAUDIOFILE");
		case Sdl_DiskAudioDelay: return QString("SDL_DISKAUDIODELAY");
		case Sdl_DspNoSelect: return QString("SDL_DSP_NOSELECT");
		case Sdl_PathDsp: return QString("SDL_PATH_DSP");
		case Sdl_Cdrom: return QString("SDL_CDROM");
		case Sdl_Debug: return QString("SDL_DEBUG");
		case Sdl_JoystickDevice: return QString("SDL_JOYSTICK_DEVICE");
		case Sdl_LinuxJoystick: return QString("SDL_LINUX_JOYSTICK");
		default: return QString();
	}
}

void QSdlWidget::SetVideoSdlVideoDriver(QSdlWidget::QSdlVideoDriver driver)
{
	this->setToEnvironment(this->getEnvironmentNameInTheList(Sdl_VideoDriver), this->getVideoDriverNameInTheList(driver));
}

void QSdlWidget::SetVideoSdlWindowId(WId wid)
{
	this->setToEnvironment(this->getEnvironmentNameInTheList(Sdl_WindowId), QString("0x").append(QString::number(wid, 16)));
}

void QSdlWidget::SetAudioSdlAudioDriver(QSdlWidget::QSdlAudioDriver driver)
{
	this->setToEnvironment(this->getEnvironmentNameInTheList(Sdl_AudioDriver), this->getAudioDriverNameInTheList(driver));
}
