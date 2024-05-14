QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin/adduserwindow.cpp \
    admin/adminareawindow.cpp \
    admin/edituserwindow.cpp \
    admin/listuserswindow.cpp \
    authwindow.cpp \
    client/addmachinewindow.cpp \
    client/clientareawindow.cpp \
    client/clientmachineswindow.cpp \
    client/clientrepairswindow.cpp \
    config.cpp \
    config_example.cpp \
    confirmationdialog.cpp \
    entities/basesqlobject.cpp \
    entities/machine.cpp \
    entities/order.cpp \
    entities/relationship_wrapper.cpp \
    entities/service.cpp \
    entities/user.cpp \
    main.cpp \
    messages.cpp \
    models/connections.cpp \
    models/create.cpp \
    models/delete.cpp \
    models/read.cpp \
    models/update.cpp \
    worker/aboutmachinewindow.cpp \
    worker/aboutorderwindow.cpp \
    worker/activeorderslistwindow.cpp \
    worker/aviableorderslistwindow.cpp \
    worker/completeorderwindow.cpp \
    worker/listrepairsmachinewindow.cpp \
    worker/workerareawindow.cpp

HEADERS += \
    admin/adduserwindow.h \
    admin/adminareawindow.h \
    admin/edituserwindow.h \
    admin/listuserswindow.h \
    authwindow.h \
    client/addmachinewindow.h \
    client/clientareawindow.h \
    client/clientmachineswindow.h \
    client/clientrepairswindow.h \
    confirmationdialog.h \
    entities/basesqlobject.h \
    entities/machine.h \
    entities/order.h \
    entities/relationship_wrapper.h \
    entities/service.h \
    entities/user.h \
    messages.h \
    models/db.h \
    worker/aboutmachinewindow.h \
    worker/aboutorderwindow.h \
    worker/activeorderslistwindow.h \
    worker/aviableorderslistwindow.h \
    worker/completeorderwindow.h \
    worker/listrepairsmachinewindow.h \
    worker/workerareawindow.h

FORMS += \
    admin/adduserwindow.ui \
    admin/adminareawindow.ui \
    admin/edituserwindow.ui \
    admin/listuserswindow.ui \
    authwindow.ui \
    client/addmachinewindow.ui \
    client/clientareawindow.ui \
    client/clientmachineswindow.ui \
    client/clientrepairswindow.ui \
    confirmationdialog.ui \
    worker/aboutmachinewindow.ui \
    worker/aboutorderwindow.ui \
    worker/activeorderslistwindow.ui \
    worker/aviableorderslistwindow.ui \
    worker/completeorderwindow.ui \
    worker/listrepairsmachinewindow.ui \
    worker/workerareawindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
