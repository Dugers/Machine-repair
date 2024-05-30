QT += testlib
QT -= gui

PROJECT_PATH = $$PWD/../../

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_entities_str.cpp \
    $$PROJECT_PATH/src/config.cpp \
    $$PROJECT_PATH/src/entities/basesqlobject.cpp \
    $$PROJECT_PATH/src/entities/machine.cpp \
    $$PROJECT_PATH/src/entities/order.cpp \
    $$PROJECT_PATH/src/entities/service.cpp \
    $$PROJECT_PATH/src/entities/user.cpp

HEADERS += tst_entities_str.h \
    $$PROJECT_PATH/src/entities/machine.h \
    $$PROJECT_PATH/src/entities/order.h \
    $$PROJECT_PATH/src/entities/service.h \
    $$PROJECT_PATH/src/config.h \
    $$PROJECT_PATH/src/entities/basesqlobject.h \
    $$PROJECT_PATH/src/entities/user.h \

INCLUDEPATH += $$PROJECT_PATH/src
