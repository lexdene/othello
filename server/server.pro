TEMPLATE = app
TARGET = OthelloServer

# Input
HEADERS += \
    application/jothelloserverapplication.h \
    application/jothelloserverapplicationfactory.h
SOURCES += \
    main/main.cpp \
    application/jothelloserverapplication.cpp \
    application/jothelloserverapplicationfactory.cpp

include(../dgpapi.pri)
include(../common/common.pri)
include(../../roommodel/roommodel_server.pri)
