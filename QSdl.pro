#-------------------------------------------------
#
# Project created by QtCreator 2016-11-28T11:09:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = QSdl
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    QSdl/qsdlexception.cpp \
    QSdl/qsdlvideo.cpp \
    QSdl/qsdlwidget.cpp \
    QSdl/com/qsdlpixelformat.cpp \
    QSdl/com/qsdlpalette.cpp \
    QSdl/com/qsdlsurface.cpp \
    QSdl/com/qsdlvideoinfo.cpp \
    QSdl/com/qsdlkeyboardmap.cpp \
    QSdl/qsdlevent.cpp \
    QSdl/com/qsdlmousemap.cpp \
    QSdl/com/qsdlimage.cpp \
	QSdl/com/qsdlmixer.cpp \
    QSdl/qsdlmusic.cpp \
    QSdl/qsdlsound.cpp \
    QSdl/com/qsdlcolor.cpp \
    QSdl/qsdlfontimage.cpp

HEADERS  += widget.h \
    QSdl/global.h \
    QSdl/qsdlexception.h \
    QSdl/qsdlvideo.h \
    QSdl/qsdlwidget.h \
    QSdl/com/qsdlpixelformat.h \
    QSdl/com/qsdlpalette.h \
    QSdl/com/qsdlsurface.h \
    QSdl/com/qsdlvideoinfo.h \
    QSdl/com/qsdlkeyboardmap.h \
    QSdl/qsdlevent.h \
    QSdl/com/qsdlmousemap.h \
    QSdl/com/qsdlimage.h \
	QSdl/com/qsdlmixer.h \
    QSdl/qsdlmusic.h \
    QSdl/qsdlsound.h \
    QSdl/com/qsdlcolor.h \
    QSdl/qsdlfontimage.h

win32: LIBS += -L$$PWD/lib/ -llibSDL.dll
win32: LIBS += -L$$PWD/lib/ -lSDL_image
win32: LIBS += -L$$PWD/lib/ -lSDL_mixer
win32: LIBS += -L$$PWD/lib/ -lSDL_ttf

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
