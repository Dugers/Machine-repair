QT += testlib
QT -= gui

PROJECT_PATH = $$PWD/../../

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_entities_validators.cpp \
    $$PROJECT_PATH/src/config.cpp \
    $$PROJECT_PATH/src/entities/basesqlobject.cpp \
    $$PROJECT_PATH/src/entities/user.cpp

HEADERS += tst_entities_validators.h \
    $$PROJECT_PATH/src/config.h \
    $$PROJECT_PATH/src/entities/basesqlobject.h \
    $$PROJECT_PATH/src/entities/user.h \

INCLUDEPATH += $$PWD/../../src
