#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T17:35:52
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AsyncServerGui
TEMPLATE = app


SOURCES += main.cpp\
        servermain.cpp \
    theserver.cpp \
    theclient.cpp \
    thetask.cpp

HEADERS  += servermain.h \
    theserver.h \
    thetask.h \
    theclient.h

FORMS    += servermain.ui
