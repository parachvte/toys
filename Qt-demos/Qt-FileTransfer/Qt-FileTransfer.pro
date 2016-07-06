#-------------------------------------------------
#
# Project created by QtCreator 2014-11-29T02:03:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-FileTransfer
TEMPLATE = app

LIBS += -lws2_32

SOURCES += main.cpp\
        mainwindow.cpp \
    Server/SocketObj.cpp \
    Server/BufferObj.cpp \
    Server/OverlappedIO.cpp \
    Server/Server.cpp \
    Server/ThreadObj.cpp \
    Server/Notifier.cpp

HEADERS  += mainwindow.h \
    Common/InitSock.h \
    Server/SocketObj.h \
    Server/BufferObj.h \
    Server/OverlappedIO.h \
    Server/Server.h \
    Server/ThreadObj.h \
    Server/Notifier.h

FORMS    += mainwindow.ui

RESOURCES += \
    application.qrc
