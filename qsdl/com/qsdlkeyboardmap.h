#ifndef QSDLKEYBOARDMAP_H
#define QSDLKEYBOARDMAP_H

#include <QtCore>
#include <SDL/SDL_keysym.h>

class QSdlKeyboardMap
{
	QMap<SDLKey, Qt::Key> keyMap;
	QMap<SDLKey, Qt::KeyboardModifier> keyModMap;
	QMap<SDLMod, Qt::KeyboardModifier> modMap;
public:
	QSdlKeyboardMap();
	Qt::Key getQtKey(SDLKey key);
	Qt::KeyboardModifiers getQtModifier(SDLKey key, SDLMod mod = KMOD_NONE);

};

#endif // QSDLKEYBOARDMAP_H
