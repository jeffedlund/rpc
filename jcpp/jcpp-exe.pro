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

TEMPLATE = app

LIBS+=  -L../jcpp-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug/debug -ljcpp

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

SOURCES += \
    src/main/cpp/jcpp/lang/boot/Main.cpp
