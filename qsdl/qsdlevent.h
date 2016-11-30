#ifndef QSDLEVENT_H
#define QSDLEVENT_H

#include <QObject>

class QSdlEvent : public QObject
{
	Q_OBJECT
public:
	explicit QSdlEvent(QObject *parent = 0);

signals:

public slots:
};

#endif // QSDLEVENT_H