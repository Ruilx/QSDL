#ifndef QSDL_H
#define QSDL_H

#include <QtWidgets>
#include <QThread>
#include <SDL/SDL.h>
#include "global.h"
#include "qsdlexception.h"
#include "qsdlevent.h"
#include "com/qsdlsurface.h"

#define QKeyMask 0x0FFFFFFF
#define QMouseButtonMask 0x0FFFFFFF

class QSdlWidget : public QWidget
{
	Q_OBJECT
	QWidget *parent = nullptr;
	QSdlEvent *sdlEvent = new QSdlEvent();
	QList<QThread*> threadList;

	//SDL_Surface *mainSurface = nullptr;
	QSdlSurface *mainSurface = nullptr;

	QPaintEngine *paintEngine() const { return nullptr; }

	void closeEvent(QCloseEvent *event){

		QWidget::closeEvent(event);
	}

	//void keyPressEvent(QKeyEvent *event);
	//void keyReleaseEvent(QKeyEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

	void createSdlEventThread(QSdlEvent *eventObject);

public:
	enum QSdlInitDevices{
		Sdl_InitTimer = SDL_INIT_TIMER,
		Sdl_InitAudio = SDL_INIT_AUDIO,
		Sdl_InitVideo = SDL_INIT_VIDEO,
		Sdl_InitCdrom = SDL_INIT_CDROM,
		Sdl_InitJoystick = SDL_INIT_JOYSTICK,
		Sdl_InitNoParachute = SDL_INIT_NOPARACHUTE,
		Sdl_InitEventThread = SDL_INIT_EVENTTHREAD,
		Sdl_InitEverything = SDL_INIT_EVERYTHING
	};

	QSdlWidget(QSdlInitDevices devices, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Window, bool *ok = nullptr) throw(QSdlException);
	QSdlWidget(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Window, bool *ok = nullptr) throw(QSdlException);
	~QSdlWidget();

	bool initSubSystem(QSdlInitDevices devices) throw(QSdlException);
	QSdlInitDevices isInit(QSdlInitDevices devices = (QSdlInitDevices)0);

	void quitSubSystem(QSdlInitDevices devices) Q_DECL_NOTHROW;
	void quit() Q_DECL_NOTHROW;

	bool setupSurface(int width, int height, QSdlSurface::SdlSurfaceScreenBpp bpp, QSdlSurface::SdlSurfaceFlags flags = QSdlSurface::Sdl_SwSurface);
	bool blitSurface(QSdlSurface *surface, const QPoint &loc = QPoint(0, 0), const QRect &croppingArea = QRect()){
		return this->mainSurface->blitSurface(surface, loc, croppingArea);
	}

private:
	QSdlInitDevices initDevices = (QSdlInitDevices)0;

	enum QSdlEnvironment{
		// For Video
		Sdl_FbAccel,
		Sdl_FbDev,
		Sdl_FullscreenUpdate,
		Sdl_VideoDriver,
		Sdl_VideoCentered,
		Sdl_VideoWindowPos,
		Sdl_VideoGlDriver,
		Sdl_X11DgaMouse,
		Sdl_X11MouseAccel,
		Sdl_VideoX11NoDirectColor,
		Sdl_VideoX11VisualId,
		Sdl_VideoX11WmcClass,
		Sdl_VideoYuvDirect,
		Sdl_VideoYuvHwAccel,
		Sdl_WindowId,
		// For Events/Input
		Sdl_MouseRelative,
		Sdl_MouseDev,
		Sdl_MouseDevImps2,
		Sdl_MouseDrv,
		Sdl_NoRawKeyboard,
		Sdl_NoMouse,
		// For Audio
		Sdl_AudioDev,
		Sdl_AudioDriver,
		Sdl_DiskAudioFile,
		Sdl_DiskAudioDelay,
		Sdl_DspNoSelect,
		Sdl_PathDsp,
		// For CDROM
		Sdl_Cdrom,
		// For Debugging
		Sdl_Debug,
		// For Joystick
		Sdl_JoystickDevice,
		Sdl_LinuxJoystick
	};

public:
	enum QSdlVideoDriver{
		Sdl_Quartz,		// Quartz (Max OS X)
		Sdl_X11,		// X Window System
		Sdl_Dga,		// XFree86 DGA 2
		Sdl_Nanox,		// Nano-X Window System (Linux)
		Sdl_Ipod,		// iPod framebuffer (iPod)
		Sdl_Qtopia,		// Qtopia (embedded Linux)
		Sdl_Wscons,		// NetBSD/OpenBSD wscons interface (BSD)
		Sdl_Fbcon,		// Linux framebuffer console (Linux)
		Sdl_DirectFb,	// DirectFB (Linux)
		Sdl_Ps2gs,		// Playstation 2 Graphics Synthesizer (Playstation 2)
		Sdl_Ggi,		// General Graphics Interface
		Sdl_Vgl,		// FreeBSD Video Graphics Library (BSD)
		Sdl_Svgalib,	// SVGAlib (Linux)
		Sdl_Gapi,		// Pocket PC Game API (Windows CE)
		Sdl_Windib,		// Windows 95/98/NT/2000 GDI (Win32)
		Sdl_Directx,	// Microsoft DirectX (Win32)
		Sdl_Bwindow,	// BDirectWindow (BeOS)
		Sdl_Toolbox,	// MacOS ROM Toolbox (MacOS Classic)
		Sdl_Dspvideo,	// DrawSprocket (MacOS Classic)
		Sdl_Photon,		// QNX Photon (QNX)
		Sdl_Epocvideo,	// EPOC (EPOC)
		Sdl_Xbios,		// Atari XBIOS (Atari)
		Sdl_Gem,		// Atari GEM (Atari)
		Sdl_Picogui,	// PicoGUI
		Sdl_Dcvideo,	// Dreamcast video (Dreamcast)
		Sdl_Ndsvideo,	// Nintendo DS video (Nintendo DS)
		Sdl_Riscos,		// RISC OS (RISCOS)
		Sdl_Os2fslib,	// FSLib (OS/2)
		Sdl_Aalib,		// ASCII Art Library
		Sdl_Dummyvideo	// dummy driver (no output)
	};

	enum QSdlAudioDriver{
		Sdl_Openbsd,	// (OpenBSD)
		Sdl_Dspaudio,	// OSS /dev/dsp (no DMA): Linux, Solarsis, BSD etc)
		Sdl_Dma,		// OSS /dev/dsp (DMA): Linux, Solaris, BSD etc)
		Sdl_Alsa,		// ALSA (Linux)
		Sdl_Pulse,		// PulseAudio (POSIX, Win32)
		Sdl_Qsanto,		// QNX6 QSA-NTO audio (QNX)
		Sdl_Audio,		// Unix style /dev/audio: (SunOS, Solaris etc)
		Sdl_Al,			// Irix DMedia audio (Irix)
		Sdl_Artsc,		// aRts (Analog Realtime Synthesizer)
		Sdl_Esd,		// Enlightenment Sound Daemon
		Sdl_Nas,		// Network Audio System (POSIX)
		Sdl_Dsound,		// DirectSound (Win32)
		Sdl_Waveout,	// Windows WaveOut (Win32)
		Sdl_Paud,		// Paudio (AIX)
		Sdl_Baudio,		// BSoundPlayer (BeOS)
		Sdl_Coreaudio,	// MacOS X CoreAudio (MacOS X)
		Sdl_Sndmgr,		// MacOS SoundManager 3.0 (old MacOS)
		Sdl_Mint_gsxb,	// MiNT GSXB audio driver
		Sdl_Mint_mcsn,	// MiNT MCSN audio driver
		Sdl_Mint_stfa,	// MiNT STFA audio driver
		Sdl_Mint_xbios,	// MiNT XBIOS audio driver
		Sdl_Mint_dma8,	// MiNT DMA 8 bits audio driver
		Sdl_Disk,		// output to file (all platforms)
		Sdl_Dummyaudio,	// dummy driver (no output)
		Sdl_DcAudio,	// Dreamcast AICA audio
		Sdl_Ndsaudio,	// Nintendo DS audio
		Sdl_Waveout2,	// Tru64 MME WaveOut
		Sdl_Dart,		// OS/2 Direct Audio RouTines (DART)
		Sdl_Epocaudio	// EPOC streaming audio
	};
private:
	void setToEnvironment(QString name, QString value);
	QString getVideoDriverNameInTheList(QSdlVideoDriver driver);
	QString getAudioDriverNameInTheList(QSdlAudioDriver driver);
	QString getEnvironmentNameInTheList(QSdlEnvironment env);

public:
	//void SetVideoSdlFbAccel(QString value);
	//void SetVideoSdlFbDev(QString value);
	//void SetVideoSdlFullscreenUpdate(QString value);
	void SetVideoSdlVideoDriver(QSdlVideoDriver driver);

	void SetVideoSdlWindowId(WId wid);

	void SetAudioSdlAudioDriver(QSdlAudioDriver driver);

	bool update();

signals:

public slots:

private slots:
	void sdlEventShowHideSlot(bool show);

	void sdlEventKeySigSlot(int eventType, int eventKey, int eventModifiers, QString text);

	void sdlEventQuitSlot();

	void sdlEventMouseMoveSigSlot(int eventMouseButtons, QPoint location);

	void joinThread(QThread *quitedThread);
};

#endif // QSDL_H
