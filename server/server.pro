TEMPLATE = app
TARGET =

# Input
HEADERS += \
    application/jothelloserverapplication.h \
    application/jothelloserverapplicationfactory.h
SOURCES += \
    main/main.cpp \
    application/jothelloserverapplication.cpp \
    application/jothelloserverapplicationfactory.cpp

include(../../Dlut-Game-Platform/api/api.pri)
include(../common/common.pri)
include(../../roommodel/roommodel_server.pri)
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=lib/
