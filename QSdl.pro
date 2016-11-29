#-------------------------------------------------
#
# Project created by QtCreator 2016-11-28T11:09:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSdl
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    QSdl/qsdlexception.cpp \
    QSdl/qsdlvideo.cpp \
    QSdl/qsdlwidget.cpp

HEADERS  += widget.h \
    QSdl/global.h \
    QSdl/qsdlexception.h \
    QSdl/qsdlvideo.h \
    QSdl/qsdlwidget.h

win32: LIBS += -L$$PWD/lib/ -llibSDL.dll

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
