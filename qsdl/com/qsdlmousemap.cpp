#include "qsdlmousemap.h"


QSdlMouseMap::QSdlMouseMap(){
	this->mouseButtonMap.clear();
	mouseButtonMap.insert(Sdl_MouseLeftButton, Qt::LeftButton);
	mouseButtonMap.insert(Sdl_MouseMidButton, Qt::MidButton);
	mouseButtonMap.insert(Sdl_MouseRightButton, Qt::RightButton);
	mouseButtonMap.insert(Sdl_MouseWheelUp, Qt::NoButton);
	mouseButtonMap.insert(Sdl_MouseWheelDown, Qt::NoButton);
	mouseButtonMap.insert(Sdl_MouseX1Button, Qt::XButton1);
	mouseButtonMap.insert(Sdl_MouseX2Button, Qt::XButton2);
}

Qt::MouseButtons QSdlMouseMap::getQtMouseButton(QSdlMouseMap::SdlMouseButton mouseButton){
	int m = (int)mouseButton;
	int qtM = 0x00000000;
	for(int i = 0x00000001; i <= 0x40000000 && i > 0; i <<= 1){
		int buttonMask = m & i;
		int qtMask = (int)mouseButtonMap.value((SdlMouseButton)buttonMask, (Qt::MouseButton)-1);
		if(qtMask != -1){
			qtM |= qtMask;
		}
	}
	return (Qt::MouseButtons)qtM;
}
