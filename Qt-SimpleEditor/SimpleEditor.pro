######################################################################
# Automatically generated by qmake (3.0) Sun Oct 5 23:40:40 2014
######################################################################

TEMPLATE = app
TARGET = SimpleEditor
INCLUDEPATH += .

QT += qml quick widgets

deployment += \
    deployment.pri

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += src/main.cpp

RESOURCES += qml.qrc

OTHER_FILES += images/copy.ico

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

