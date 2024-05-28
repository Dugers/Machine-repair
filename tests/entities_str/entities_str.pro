QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_entities_str.cpp \
    ../../src/config.cpp \
    ../../src/entities/basesqlobject.cpp \
    ../../src/entities/machine.cpp \
    ../../src/entities/order.cpp \
    ../../src/entities/service.cpp \
    ../../src/entities/user.cpp

HEADERS += \
    ../../src/entities/machine.h \
    ../../src/entities/order.h \
    ../../src/entities/service.h \
    tst_entities_str.h \
    ../../src/config.h \
    ../../src/entities/basesqlobject.h \
    ../../src/entities/user.h \

INCLUDEPATH += $$PWD/../../src
