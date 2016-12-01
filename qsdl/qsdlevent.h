#ifndef QSDLEVENT_H
#define QSDLEVENT_H

#include <QObject>
#include "global.h"
#include "com/qsdlkeyboardmap.h"
#include "com/qsdlmousemap.h"
#include <SDL/SDL_events.h>
#include <SDL/SDL_keyboard.h>
#include <SDL/SDL_keysym.h>
#include <QEvent>

class QSdlEvent : public QObject
{
	Q_OBJECT
	bool doExit = false;
	QSdlKeyboardMap *qKeyMap = new QSdlKeyboardMap();
	QSdlMouseMap *qMouseMap = new QSdlMouseMap();

public:
	explicit QSdlEvent();
	~QSdlEvent(){}

signals:
	void sdlQuitSig();
	void sdlShowHideSig(bool show);
	void sdlKeySig(int eventType, int key, int modifiers, QString keyString);
	void sdlMouseMoveSig(int mouseButton, QPoint location);

	void finish(QThread *currentThread);
public slots:
	void listenSdlEvent();
	void forceExit();
};

#endif // QSDLEVENT_H
