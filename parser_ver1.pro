TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

OURCES += main.cpp

INCLUDEPATH += /usr/lib/x86_64-linux-gnu/

LIBS += -lcurl

SOURCES += \
        main.cpp
