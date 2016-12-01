#ifndef QSDLMOUSEMAP_H
#define QSDLMOUSEMAP_H

#include <QtCore>
#include <SDL/SDL_mouse.h>
#include <SDL/SDL_events.h>
#include "../global.h"

class QSdlMouseMap
{
public:
	enum SdlMouseButton{
		Sdl_MouseLeftButton = 1,
		Sdl_MouseMidButton = 2,
		Sdl_MouseRightButton = 4,
		Sdl_MouseWheelUp = 8,
		Sdl_MouseWheelDown = 16,
		Sdl_MouseX1Button = 32,
		Sdl_MouseBackButton = Sdl_MouseX1Button,
		Sdl_MouseX2Button = 64,
		Sdl_MouseForwardButton = Sdl_MouseX2Button
	};

//	typedef union Sdl_MouseOrWheelButton{
//		SdlMouseButton mouseButton;
//		int wheelDelta;
//	}SdlMouseOrWheelButton;

	QSdlMouseMap();
	Qt::MouseButtons getQtMouseButton(SdlMouseButton mouseButton);

private:
	QMap<SdlMouseButton, Qt::MouseButton> mouseButtonMap;
};

#endif // QSDLMOUSEMAP_H
