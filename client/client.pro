#-------------------------------------------------
#
# Project created by QtCreator 2011-11-23T19:45:43
#
#-------------------------------------------------

TARGET = client
TEMPLATE = app


SOURCES += \
    main/main.cpp \
    gui/jothellowindow.cpp \
    application/jothelloclientapplication.cpp \
    gui/jothellowidget.cpp \
    gui/jmemorylineedit.cpp \
    game/jothellomapper.cpp \
    application/jothelloinput.cpp \
    application/jothellooutput.cpp

HEADERS  += \
    gui/jothellowindow.h \
    application/jothelloclientapplication.h \
    gui/jothellowidget.h \
    gui/jmemorylineedit.h \
    game/jothellomapper.h \
    application/jothelloinput.h \
    application/jothellooutput.h

FORMS    += \
    gui/jothellowindow.ui \
    gui/jothellowidget.ui

include(../../Dlut-Game-Platform/api/api.pri)
include(../common/common.pri)
include(../../roommodel/roommodel_client.pri)
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=lib/

RESOURCES += \
    res/res.qrc
