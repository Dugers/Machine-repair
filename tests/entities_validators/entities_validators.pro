QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_entities_validators.cpp \
    ../../src/config.cpp \
    ../../src/entities/basesqlobject.cpp \
    ../../src/entities/user.cpp

HEADERS += \
    ../../src/config.h \
    ../../src/entities/basesqlobject.h \
    ../../src/entities/user.h \
    tst_entities_validators.h

INCLUDEPATH += $$PWD/../../src
