#-------------------------------------------------
#
# Project created by QtCreator 2013-05-01T11:38:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = jcpp-exe
CONFIG   += console
CONFIG   -= app_bundle

#QMAKE_CXXFLAGS += -std=c++11

QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-variable
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

LIBS+= -L../jcpp-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug/debug -ljcpp
#-L../gc-7.2/.libs -lcygcord-1 -lcyggc-1

INCLUDEPATH += \
        src/main/cpp/jcpp/ \
        src/main/cpp/jcpp/lang \
        src/main/cpp/jcpp/lang/boot \
        src/main/cpp/jcpp/io \
        src/main/cpp/jcpp/io/impl \
        src/main/cpp/jcpp/util \
        src/main/cpp/jcpp/util/concurrent \
        src/main/cpp/jcpp/lang/exception \
        src/main/cpp/jcpp/lang/reflect \
        src/main/cpp/jcpp/rmi/ \
        src/main/cpp/jcpp/rmi/server \
        src/main/cpp/jcpp/rmi/server/impl \
        src/main/cpp/jcpp/rmi/server/impl/gateway \
        src/main/cpp/jcpp/rmi/server/impl/transport \
        src/main/cpp/jcpp/rmi/server/impl/connection \
        src/main/cpp/jcpp/rmi/server/impl/connection/serialization \
        src/main/cpp/jcpp/net \
        src/main/cpp/jcpp/security \
        ../gc-7.2/include \

SOURCES += \
    src/main/cpp/jcpp/lang/boot/Main.cpp
