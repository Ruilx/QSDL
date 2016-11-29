#include "qsdlexception.h"

QSdlException::QSdlException(const QString &errorString) Q_DECL_NOTHROW
{
	this->errorString = QString(errorString);
	this->sdlErrorString = QString(SDL_GetError());

	qCritical() << QObject::tr("[QSdlException]: %1").arg(this->getErrorString());
}
