TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lws2_32

SOURCES += main.c

HEADERS += \
    icmp.h \
    initsock.h

OTHER_FILES +=
