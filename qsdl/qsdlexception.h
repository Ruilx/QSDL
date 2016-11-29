#ifndef QSDLEXCEPTION_H
#define QSDLEXCEPTION_H

#include <QCoreApplication>
#include "global.h"
#include <SDL/SDL_error.h>
#include <QDebug>

class QSdlException
{
	QString errorString;
	QString sdlErrorString;
public:
	explicit QSdlException(const QString &errorString) Q_DECL_NOTHROW;

	QString getSdlErrorString() const{
		return this->sdlErrorString;
	}

	QString getErrorString() const{
		QString old = this->errorString;
		old.replace(QString("{$sdl_error}"), this->sdlErrorString, Qt::CaseInsensitive);
		return old;
	}

	static void setError(QString error){
		SDL_SetError(error.toLocal8Bit());
	}

	static void clearError(){
		SDL_ClearError();
	}

};

#endif // QSDLEXCEPTION_H
