#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T19:04:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT += network

TARGET = io
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += \
        src/main/cpp/jcpp/ \
	src/main/cpp/jcpp/lang \
	src/main/cpp/jcpp/io \
	src/main/cpp/jcpp/io/impl \
	src/main/cpp/jcpp/util \
	src/main/cpp/jcpp/lang/exception \
	src/main/cpp/jcpp/lang/reflect \
	src/test/cpp/jcpp\
	src/test/cpp/jcpp/lang \
	src/test/cpp/jcpp/io

SOURCES += \
    src/test/cpp/jcpp/main.cpp \
    src/main/cpp/jcpp/lang/JClass.cpp \
    src/main/cpp/jcpp/lang/JClassLoader.cpp \
    src/main/cpp/jcpp/lang/JObject.cpp \
    src/main/cpp/jcpp/lang/reflect/JMethod.cpp \
    src/main/cpp/jcpp/lang/reflect/JProxy.cpp \
    src/main/cpp/jcpp/lang/reflect/JInvocationHandler.cpp \
    src/main/cpp/jcpp/lang/reflect/JField.cpp \
    src/main/cpp/jcpp/lang/exception/JNullPointerException.cpp \
    src/main/cpp/jcpp/lang/exception/JIndexOutOfBoundsException.cpp \
    src/main/cpp/jcpp/lang/exception/JException.cpp \
    src/main/cpp/jcpp/lang/JString.cpp \
    src/main/cpp/jcpp/lang/JEnum.cpp \
    src/main/cpp/jcpp/util/JArrayList.cpp \
    src/main/cpp/jcpp/io/JSerializable.cpp \
    src/main/cpp/jcpp/util/JHashtable.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveBoolean.cpp \
    src/main/cpp/jcpp/lang/JBoolean.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveByte.cpp \
    src/main/cpp/jcpp/lang/JByte.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveChar.cpp \
    src/main/cpp/jcpp/lang/JChar.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveDouble.cpp \
    src/main/cpp/jcpp/lang/JDouble.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveFloat.cpp \
    src/main/cpp/jcpp/lang/JFloat.cpp \
    src/main/cpp/jcpp/lang/JPrimtiveInt.cpp \
    src/main/cpp/jcpp/lang/JInteger.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveLong.cpp \
    src/main/cpp/jcpp/lang/JLong.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveShort.cpp \
    src/main/cpp/jcpp/lang/JShort.cpp \
    src/main/cpp/jcpp/io/JInputStream.cpp \
    src/main/cpp/jcpp/io/JDataInputStream.cpp \
    src/main/cpp/jcpp/io/QtDataInputStream.cpp \
    src/main/cpp/jcpp/io/JObjectStreamClass.cpp \
    src/main/cpp/jcpp/io/JObjectInputStream.cpp \
    src/main/cpp/jcpp/lang/exception/JNoSuchFieldException.cpp \
    src/main/cpp/jcpp/lang/exception/JNoSuchMethodException.cpp \
    src/main/cpp/jcpp/lang/exception/JInstantiationException.cpp \
    src/main/cpp/jcpp/lang/exception/JClassNotFoundException.cpp \
    src/main/cpp/jcpp/lang/JNumber.cpp \
    src/main/cpp/jcpp/lang/exception/JIllegalArgumentException.cpp \
    src/main/cpp/jcpp/lang/JStackTraceElement.cpp \
    src/main/cpp/jcpp/lang/exception/JThrowable.cpp \
    src/main/cpp/jcpp/lang/exception/JRuntimeException.cpp \
    src/main/cpp/jcpp/io/JUTFDataFormatException.cpp \
    src/main/cpp/jcpp/io/JIOException.cpp \
    src/main/cpp/jcpp/io/JEOFException.cpp \
    src/main/cpp/jcpp/lang/JPrimitiveArray.cpp \
    src/main/cpp/jcpp/io/impl/SerialCallbackContext.cpp \
    src/main/cpp/jcpp/io/impl/HandleTable.cpp \
    src/main/cpp/jcpp/io/impl/HandleList.cpp \
    src/main/cpp/jcpp/io/impl/BlockDataInputStream.cpp \
    src/main/cpp/jcpp/io/JObjectStreamException.cpp \
    src/main/cpp/jcpp/io/JInvalidClassException.cpp \
    src/main/cpp/jcpp/lang/exception/JError.cpp \
    src/main/cpp/jcpp/lang/exception/JVirtualMachineError.cpp \
    src/main/cpp/jcpp/lang/exception/JInternalError.cpp \
    src/main/cpp/jcpp/io/JStreamCorruptedException.cpp \
    src/main/cpp/jcpp/io/JOptionalDataException.cpp \
    src/main/cpp/jcpp/io/JNotActiveException.cpp \
    src/test/cpp/jcpp/JSampleObject.cpp \
    src/main/cpp/jcpp/lang/exception/JIllegalStateException.cpp \
    src/main/cpp/jcpp/lang/exception/JUnsupportedOperationException.cpp \
    src/main/cpp/jcpp/lang/exception/JClassCastException.cpp \
    src/main/cpp/jcpp/io/JOutputStream.cpp \
    src/main/cpp/jcpp/io/JDataOutputStream.cpp \
    src/main/cpp/jcpp/io/impl/BlockDataOutputStream.cpp \
    src/main/cpp/jcpp/io/impl/OutputHandleTable.cpp \
    src/main/cpp/jcpp/io/JObjectOutputStream.cpp \
    src/main/cpp/jcpp/io/JObjectStreamField.cpp \
    src/main/cpp/jcpp/lang/JVoid.cpp \
    src/main/cpp/jcpp/io/JExternalizable.cpp \
    src/main/cpp/jcpp/io/JNotSerializableException.cpp \
    src/main/cpp/jcpp/io/QtDataOutputStream.cpp \
    src/main/cpp/jcpp/lang/JInterface.cpp \
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
    src/main/cpp/jcpp/lang/reflect/JAccessibleObject.cpp \
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
    src/main/cpp/jcpp/lang/reflect/JPackage.cpp \
    src/main/cpp/jcpp/JCPP.cpp \
    src/main/cpp/jcpp/io/JIO.cpp \
    src/main/cpp/jcpp/lang/JLANG.cpp \
    src/main/cpp/jcpp/lang/reflect/JREFLECT.cpp \
    src/main/cpp/jcpp/util/JUTIL.cpp
    
    
LIBS += -lws2_32

HEADERS += \
    src/main/cpp/jcpp/lang/JClass.h \
    src/main/cpp/jcpp/lang/JClassLoader.h \
    src/main/cpp/jcpp/lang/JObject.h \
    src/main/cpp/jcpp/lang/JClassBuilder.h \
    src/main/cpp/jcpp/lang/reflect/JMethod.h \
    src/main/cpp/jcpp/lang/reflect/JProxy.h \
    src/main/cpp/jcpp/lang/reflect/JInvocationHandler.h \
    src/main/cpp/jcpp/lang/reflect/JField.h \
    src/main/cpp/jcpp/lang/exception/JNullPointerException.h \
    src/main/cpp/jcpp/lang/exception/JIndexOutOfBoundsException.h \
    src/main/cpp/jcpp/lang/exception/JException.h \
    src/main/cpp/jcpp/lang/JString.h \
    src/main/cpp/jcpp/lang/JEnum.h \
    src/main/cpp/jcpp/util/JArrayList.h \
    src/main/cpp/jcpp/io/JSerializable.h \
    src/main/cpp/jcpp/util/JCollection.h \
    src/main/cpp/jcpp/util/JBits.h \
    src/main/cpp/jcpp/util/JHashtable.h \
    src/main/cpp/jcpp/lang/JPrimitiveBoolean.h \
    src/main/cpp/jcpp/lang/JBoolean.h \
    src/main/cpp/jcpp/lang/JPrimitiveByte.h \
    src/main/cpp/jcpp/lang/JByte.h \
    src/main/cpp/jcpp/lang/JPrimitiveChar.h \
    src/main/cpp/jcpp/lang/JChar.h \
    src/main/cpp/jcpp/lang/JPrimitiveDouble.h \
    src/main/cpp/jcpp/lang/JDouble.h \
    src/main/cpp/jcpp/lang/JPrimitiveFloat.h \
    src/main/cpp/jcpp/lang/JFloat.h \
    src/main/cpp/jcpp/lang/JPrimitiveInt.h \
    src/main/cpp/jcpp/lang/JInteger.h \
    src/main/cpp/jcpp/lang/JPrimitiveLong.h \
    src/main/cpp/jcpp/lang/JLong.h \
    src/main/cpp/jcpp/lang/JPrimitiveShort.h \
    src/main/cpp/jcpp/lang/JShort.h \
    src/main/cpp/jcpp/io/JObjectStreamConstants.h \
    src/main/cpp/jcpp/io/JInputStream.h \
    src/main/cpp/jcpp/io/JDataInputStream.h \
    src/main/cpp/jcpp/io/QtDataInputStream.h \
    src/main/cpp/jcpp/io/JObjectStreamClass.h \
    src/main/cpp/jcpp/io/JObjectInputStream.h \
    src/main/cpp/jcpp/util/Collections.h \
    src/main/cpp/jcpp/lang/exception/JNoSuchFieldException.h \
    src/main/cpp/jcpp/lang/exception/JNoSuchMethodException.h \
    src/main/cpp/jcpp/lang/exception/JInstantiationException.h \
    src/main/cpp/jcpp/lang/exception/JClassNotFoundException.h \
    src/main/cpp/jcpp/lang/JNumber.h \
    src/main/cpp/jcpp/lang/exception/JIllegalArgumentException.h \
    src/main/cpp/jcpp/lang/exception/JThrowable.h \
    src/main/cpp/jcpp/lang/JStackTraceElement.h \
    src/main/cpp/jcpp/lang/exception/JRuntimeException.h \
    src/main/cpp/jcpp/io/JUTFDataFormatException.h \
    src/main/cpp/jcpp/io/JIOException.h \
    src/main/cpp/jcpp/io/JEOFException.h \
    src/main/cpp/jcpp/lang/JPrimitiveArray.h \
    src/main/cpp/jcpp/io/impl/SerialCallbackContext.h \
    src/main/cpp/jcpp/io/impl/HandleTable.h \
    src/main/cpp/jcpp/io/impl/HandleList.h \
    src/main/cpp/jcpp/io/impl/BlockDataInputStream.h \
    src/main/cpp/jcpp/io/JObjectStreamException.h \
    src/main/cpp/jcpp/io/JInvalidClassException.h \
    src/main/cpp/jcpp/lang/exception/JError.h \
    src/main/cpp/jcpp/lang/exception/JVirtualMachineError.h \
    src/main/cpp/jcpp/lang/exception/JInternalError.h \
    src/main/cpp/jcpp/io/JStreamCorruptedException.h \
    src/main/cpp/jcpp/io/JOptionalDataException.h \
    src/main/cpp/jcpp/io/JNotActiveException.h \
    src/test/cpp/jcpp/JSampleObject.h \
    src/main/cpp/jcpp/io/JIO.h \
    src/main/cpp/jcpp/lang/exception/JIllegalStateException.h \
    src/main/cpp/jcpp/lang/exception/JUnsupportedOperationException.h \
    src/main/cpp/jcpp/lang/exception/JClassCastException.h \
    src/main/cpp/jcpp/io/JOutputStream.h \
    src/main/cpp/jcpp/io/JDataOutputStream.h \
    src/main/cpp/jcpp/io/impl/BlockDataOutputStream.h \
    src/main/cpp/jcpp/io/impl/OutputHandleTable.h \
    src/main/cpp/jcpp/io/JObjectOutputStream.h \
    src/main/cpp/jcpp/io/JObjectStreamField.h \
    src/main/cpp/jcpp/lang/JVoid.h \
    src/main/cpp/jcpp/io/JExternalizable.h \
    src/main/cpp/jcpp/io/JNotSerializableException.h \
    src/main/cpp/jcpp/io/QtDataOutputStream.h \
    src/main/cpp/jcpp/lang/Object.h \
    src/main/cpp/jcpp/lang/JInterface.h \
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
    src/main/cpp/jcpp/lang/reflect/JAccessibleObject.h \
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
    src/main/cpp/jcpp/lang/reflect/JPackage.h \
    src/main/cpp/jcpp/JCPP.h \
    src/main/cpp/jcpp/lang/JLANG.h \
    src/main/cpp/jcpp/lang/reflect/JREFLECT.h \
    src/main/cpp/jcpp/util/JUTIL.h
    
