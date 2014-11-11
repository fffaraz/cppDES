TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    des.cpp \
    des3.cpp \
    descbc.cpp \
    fileencryption.cpp

HEADERS += \
    des.h \
    des_data.h \
    tests.h \
    des3.h \
    descbc.h \
    fileencryption.h

