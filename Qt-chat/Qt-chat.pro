QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat-demo
TEMPLATE = app

CONFIG += mobility
MOBILITY = 

SOURCES += main.cpp\
    ChatDialog.cpp \
    ChatClient.cpp \
    SockUtil.cpp \
    ChatServer.cpp

HEADERS  += ChatDialog.h \
    ChatClient.h \
    SockUtil.h \
    ChatServer.h

FORMS    += ChatDialog.ui
