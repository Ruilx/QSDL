#ifndef QSDLEVENT_H
#define QSDLEVENT_H

#include <QObject>
#include "global.h"
#include "com/qsdlkeyboardmap.h"
#include <SDL/SDL_events.h>
#include <SDL/SDL_keyboard.h>
#include <SDL/SDL_keysym.h>
#include <QEvent>

class QSdlEvent : public QObject
{
	Q_OBJECT
	bool doExit = false;
	QSdlKeyboardMap *qKeyMap = new QSdlKeyboardMap();
public:
	explicit QSdlEvent();

signals:
	void sdlQuitSig();
	void sdlShowHideSig(bool show);
	void sdlKeySig(int eventType, int key, int modifiers, QString keyString);
public slots:
	void listenSdlEvent(){
		SDL_Event sdlEvent;
		while(!doExit){
			int hasEvents = SDL_WaitEvent(&sdlEvent);
			if(hasEvents == 0 || sdlEvent.type == 0){
				continue;
			}
			switch(sdlEvent.type){
				case SDL_NOEVENT:
					break;
				case SDL_ACTIVEEVENT:
					if(sdlEvent.active.gain == 1){
						emit this->sdlShowHideSig(true);
					}else if(sdlEvent.active.gain == 0){
						emit this->sdlShowHideSig(false);
					}
					break;
				case SDL_KEYDOWN:
				{
					Qt::Key qKey = qKeyMap->getQtKey(sdlEvent.key.keysym.sym);
					Qt::KeyboardModifiers qMod = qKeyMap->getQtModifier(sdlEvent.key.keysym.sym, sdlEvent.key.keysym.mod);
					if(qKey != Qt::Key_unknown){
						emit this->sdlKeySig((int)QEvent::KeyPress, (int)qKey, (int)qMod, QString(SDL_GetKeyName(sdlEvent.key.keysym.sym)));
					}
					break;
				}
				case SDL_KEYUP:
				{
					Qt::Key qKey = qKeyMap->getQtKey(sdlEvent.key.keysym.sym);
					Qt::KeyboardModifiers qMod = qKeyMap->getQtModifier(sdlEvent.key.keysym.sym, sdlEvent.key.keysym.mod);
					if(qKey != Qt::Key_unknown){
						emit this->sdlKeySig((int)QEvent::KeyRelease, (int)qKey, (int)qMod, QString(SDL_GetKeyName(sdlEvent.key.keysym.sym)));
					}
				}
				default:
					break;
			}
		}
	}
};

#endif // QSDLEVENT_H
