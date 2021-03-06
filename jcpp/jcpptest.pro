#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T19:04:15
#
#-------------------------------------------------

LIBS += -lws2_32

QT       += core

QT       -= gui

QT += network

#QMAKE_CXXFLAGS += -std=c++11

#TARGET = jcpptest
TARGET = $$qtLibraryTarget(jipackageloader)
CONFIG   += console
CONFIG   += plugin
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib
#TEMPLATE = app

LIBS+=  -L../jcpp-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug/debug -ljcpp
#-L../gc-7.2/.libs -lcygcord-1 -lcyggc-1

QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-variable

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
	src/test/cpp/jcpp\
	src/test/cpp/jcpp/lang \
        src/test/cpp/jcpp/io \
        src/test/cpp/jcpp/util \
        src/test/cpp/jcpp/rmi/server/impl/connection \
        ../gc-7.2/include \

SOURCES += \
    src/test/cpp/jcpp/JSampleObject.cpp \
    src/test/cpp/jcpp/JTest.cpp \
    src/test/cpp/jcpp/lang/JThrowableTest.cpp \
    src/test/cpp/jcpp/lang/JErrorTest.cpp \
    src/test/cpp/jcpp/lang/JExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JRuntimeExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JClassCastExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JClassNotFoundExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JIllegalArgumentExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JIllegalStateExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JIndexOutOfBoundsExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JInstantiationExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JVirtualMachineErrorTest.cpp \
    src/test/cpp/jcpp/lang/JInternalErrorTest.cpp \
    src/test/cpp/jcpp/lang/JNoSuchFieldExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JNoSuchMethodExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JNullPointerExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JUnsupportedOperationExceptionTest.cpp \
    src/test/cpp/jcpp/io/JIOExceptionTest.cpp \
    src/test/cpp/jcpp/io/JObjectStreamExceptionTest.cpp \
    src/test/cpp/jcpp/io/JInvalidClassExceptionTest.cpp \
    src/test/cpp/jcpp/io/JNotActiveExceptionTest.cpp \
    src/test/cpp/jcpp/io/JNotSerializableExceptionTest.cpp \
    src/test/cpp/jcpp/io/JOptionalDataExceptionTest.cpp \
    src/test/cpp/jcpp/io/JStreamCorruptedExceptionTest.cpp \
    src/test/cpp/jcpp/io/JUTFDataFormatExceptionTest.cpp \
    src/test/cpp/jcpp/lang/JShortTest.cpp \
    src/test/cpp/jcpp/lang/JBooleanTest.cpp \
    src/test/cpp/jcpp/lang/JByteTest.cpp \
    src/test/cpp/jcpp/lang/JCharTest.cpp \
    src/test/cpp/jcpp/lang/JDoubleTest.cpp \
    src/test/cpp/jcpp/lang/JFloatTest.cpp \
    src/test/cpp/jcpp/lang/JIntegerTest.cpp \
    src/test/cpp/jcpp/lang/JLongTest.cpp \
    src/test/cpp/jcpp/lang/JStringTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveBooleanTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveByteTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveCharTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveDoubleTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveFloatTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveLongTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveShortTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveIntTest.cpp \
    src/test/cpp/jcpp/util/JArrayListTest.cpp \
    src/test/cpp/jcpp/util/JTimerTest.cpp \
    src/test/cpp/jcpp/net/JSocketTest.cpp \
    src/test/cpp/jcpp/util/concurrent/JScheduledExecutorServiceTest.cpp \
    src/test/cpp/jcpp/rmi/server/impl/transport/JTransportTest.cpp \
    src/test/cpp/jcpp/rmi/server/impl/connection/JServerTest.cpp \
    src/test/cpp/jcpp/io/JExternalizableTest.cpp \
    src/test/cpp/jcpp/io/JExternalizableObject.cpp \
    src/test/cpp/jcpp/io/JSerializableTest.cpp \
    src/test/cpp/jcpp/util/JHashMapTest.cpp \
    src/test/cpp/jcpp/util/JHashSetTest.cpp \
    src/test/cpp/jcpp/util/JHashtableTest.cpp \
    src/test/cpp/jcpp/util/JIdentityHashMapTest.cpp \
    src/test/cpp/jcpp/lang/JPrimitiveArrayTest.cpp \
    src/test/cpp/jcpp/lang/JEnumTest.cpp \
    src/test/cpp/jcpp/JEnumSample.cpp \
    src/test/cpp/jcpp/JIRemoteSample.cpp \
    src/test/cpp/jcpp/JRemoteSample.cpp \
    src/test/cpp/jcpp/JIRemoteSampleProxy.cpp \
    src/test/cpp/jcpp/lang/JStringBuilderTest.cpp \
    src/test/cpp/jcpp/lang/JStringBufferTest.cpp \
    src/test/cpp/jcpp/JTestPackageLoader.cpp \
    src/test/cpp/jcpp/JTEST_JCPP_PACKAGE.cpp \
    src/test/cpp/jcpp/JTestLauncher.cpp
    
    
HEADERS += \
    src/test/cpp/jcpp/JSampleObject.h \
    src/test/cpp/jcpp/lang/JThrowableTest.h \
    src/test/cpp/jcpp/JTest.h \
    src/test/cpp/jcpp/lang/JErrorTest.h \
    src/test/cpp/jcpp/lang/JExceptionTest.h \
    src/test/cpp/jcpp/lang/JRuntimeExceptionTest.h \
    src/test/cpp/jcpp/lang/JClassCastExceptionTest.h \
    src/test/cpp/jcpp/lang/JClassNotFoundExceptionTest.h \
    src/test/cpp/jcpp/lang/JIllegalArgumentExceptionTest.h \
    src/test/cpp/jcpp/lang/JIllegalStateExceptionTest.h \
    src/test/cpp/jcpp/lang/JIndexOutOfBoundsExceptionTest.h \
    src/test/cpp/jcpp/lang/JInstantiationExceptionTest.h \
    src/test/cpp/jcpp/lang/JVirtualMachineErrorTest.h \
    src/test/cpp/jcpp/lang/JInternalErrorTest.h \
    src/test/cpp/jcpp/lang/JNoSuchFieldExceptionTest.h \
    src/test/cpp/jcpp/lang/JNoSuchMethodExceptionTest.h \
    src/test/cpp/jcpp/lang/JNullPointerExceptionTest.h \
    src/test/cpp/jcpp/lang/JUnsupportedOperationExceptionTest.h \
    src/test/cpp/jcpp/io/JIOExceptionTest.h \
    src/test/cpp/jcpp/io/JObjectStreamExceptionTest.h \
    src/test/cpp/jcpp/io/JInvalidClassExceptionTest.h \
    src/test/cpp/jcpp/io/JNotActiveExceptionTest.h \
    src/test/cpp/jcpp/io/JNotSerializableExceptionTest.h \
    src/test/cpp/jcpp/io/JOptionalDataExceptionTest.h \
    src/test/cpp/jcpp/io/JStreamCorruptedExceptionTest.h \
    src/test/cpp/jcpp/io/JUTFDataFormatExceptionTest.h \
    src/test/cpp/jcpp/lang/JShortTest.h \
    src/test/cpp/jcpp/lang/JBooleanTest.h \
    src/test/cpp/jcpp/lang/JByteTest.h \
    src/test/cpp/jcpp/lang/JCharTest.h \
    src/test/cpp/jcpp/lang/JDoubleTest.h \
    src/test/cpp/jcpp/lang/JFloatTest.h \
    src/test/cpp/jcpp/lang/JIntegerTest.h \
    src/test/cpp/jcpp/lang/JLongTest.h \
    src/test/cpp/jcpp/lang/JStringTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveBooleanTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveCharTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveByteTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveDoubleTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveFloatTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveLongTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveShortTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveIntTest.h \
    src/test/cpp/jcpp/util/JArrayListTest.h \
    src/test/cpp/jcpp/util/JTimerTest.h \
    src/test/cpp/jcpp/net/JSocketTest.h \
    src/test/cpp/jcpp/util/concurrent/JScheduledExecutorServiceTest.h \
    src/test/cpp/jcpp/rmi/server/impl/transport/JTransportTest.h \
    src/test/cpp/jcpp/rmi/server/impl/connection/JServerTest.h \
    src/test/cpp/jcpp/io/JExternalizableTest.h \
    src/test/cpp/jcpp/io/JExternalizableObject.h \
    src/test/cpp/jcpp/io/JSerializableTest.h \
    src/test/cpp/jcpp/util/JHashMapTest.h \
    src/test/cpp/jcpp/util/JHashSetTest.h \
    src/test/cpp/jcpp/util/JHashtableTest.h \
    src/test/cpp/jcpp/util/JIdentityHashMapTest.h \
    src/test/cpp/jcpp/lang/JPrimitiveArrayTest.h \
    src/test/cpp/jcpp/lang/JEnumTest.h \
    src/test/cpp/jcpp/JEnumSample.h \
    src/test/cpp/jcpp/JIRemoteSample.h \
    src/test/cpp/jcpp/JRemoteSample.h \
    src/test/cpp/jcpp/JIRemoteSampleProxy.h \
    src/test/cpp/jcpp/lang/JStringBuilderTest.h \
    src/test/cpp/jcpp/lang/JStringBufferTest.h \
    src/test/cpp/jcpp/JTestPackageLoader.h \
    src/test/cpp/jcpp/JTEST_JCPP_PACKAGE.h \
    src/test/cpp/jcpp/JTestLauncher.h
    
    
OTHER_FILES += \
    todo.txt
