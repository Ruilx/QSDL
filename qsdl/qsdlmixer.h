#ifndef QSDLMIXER_H
#define QSDLMIXER_H

#include <QObject>

class QSdlMixer : public QObject
{
	Q_OBJECT
public:
	explicit QSdlMixer(QObject *parent = 0);

signals:

public slots:
};

#endif // QSDLMIXER_H