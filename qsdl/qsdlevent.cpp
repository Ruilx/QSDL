#include "qsdlevent.h"

QSdlEvent::QSdlEvent() : QObject(nullptr)
{

}

void QSdlEvent::listenSdlEvent(){
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
					emit this->sdlKeySig((int)QEvent::KeyPress, (int)(qKey), (int)qMod, QString(SDL_GetKeyName(sdlEvent.key.keysym.sym)));
				}
				break;
			}
			case SDL_KEYUP:
			{
				Qt::Key qKey = qKeyMap->getQtKey(sdlEvent.key.keysym.sym);
				Qt::KeyboardModifiers qMod = qKeyMap->getQtModifier(sdlEvent.key.keysym.sym, sdlEvent.key.keysym.mod);
				if(qKey != Qt::Key_unknown){
					emit this->sdlKeySig((int)QEvent::KeyRelease, (int)(qKey), (int)qMod, QString(SDL_GetKeyName(sdlEvent.key.keysym.sym)));
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
//				qDebug() << "MouseMove: State:" << QString::number(sdlEvent.motion.state, 16)
//						 << "Point:" << tr("(%1, %2)").arg(sdlEvent.motion.x).arg(sdlEvent.motion.y)
//						 << "Relat:" << tr("(%1, %2)").arg(sdlEvent.motion.xrel).arg(sdlEvent.motion.yrel)
//						 << "Which:" << sdlEvent.motion.which;
				Qt::MouseButtons mouseButton = this->qMouseMap->getQtMouseButton((QSdlMouseMap::SdlMouseButton)sdlEvent.motion.state);
				QPoint location(sdlEvent.motion.x, sdlEvent.motion.y);
				emit this->sdlMouseMoveSig((int)mouseButton, location);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_JOYAXISMOTION:
				break;
			case SDL_JOYBALLMOTION:
				break;
			case SDL_JOYHATMOTION:
				break;
			case SDL_JOYBUTTONDOWN:
				break;
			case SDL_JOYBUTTONUP:
				break;
			case SDL_QUIT:
			{
				this->doExit = true;
				break;
			}
			case SDL_SYSWMEVENT:
				break;
			case SDL_EVENT_RESERVEDA:
				break;
			case SDL_EVENT_RESERVEDB:
				break;
			case SDL_VIDEORESIZE:
				break;
			case SDL_VIDEOEXPOSE:
				break;
			case SDL_EVENT_RESERVED2:
				break;
			case SDL_EVENT_RESERVED3:
				break;
			case SDL_EVENT_RESERVED4:
				break;
			case SDL_EVENT_RESERVED5:
				break;
			case SDL_EVENT_RESERVED6:
				break;
			case SDL_EVENT_RESERVED7:
				break;
			case SDL_USEREVENT:
				break;
			case SDL_NUMEVENTS:
				break;
			default:
				break;
		}
	}
	emit finish(QThread::currentThread());
}

void QSdlEvent::forceExit()
{
	this->doExit = true;
}
