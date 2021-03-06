#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T19:04:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT += network

TARGET = jcpp
CONFIG   += console
CONFIG   -= app_bundle

DEFINES += JCPP_LIBRARY

TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lws2_32
#-L../gc-7.2/.libs -lcygcord-1 -lcyggc-1

QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-variable

INCLUDEPATH += \
        src/main/cpp/jcpp/ \
	src/main/cpp/jcpp/lang \
	src/main/cpp/jcpp/io \
	src/main/cpp/jcpp/io/impl \
	src/main/cpp/jcpp/util \
        src/main/cpp/jcpp/util/concurrent \
        src/main/cpp/jcpp/util/logging \
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
        src/main/cpp/jcpp/nio \
        src/main/cpp/jcpp/nio/file \
        ../gc-7.2/include \

SOURCES += \
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
    src/main/cpp/jcpp/lang/JPrimitiveArray.cpp \
    src/main/cpp/jcpp/lang/JShort.cpp \
    src/main/cpp/jcpp/lang/exception/JNoSuchFieldException.cpp \
    src/main/cpp/jcpp/lang/exception/JNoSuchMethodException.cpp \
    src/main/cpp/jcpp/lang/exception/JInstantiationException.cpp \
    src/main/cpp/jcpp/lang/exception/JClassNotFoundException.cpp \
    src/main/cpp/jcpp/lang/JNumber.cpp \
    src/main/cpp/jcpp/lang/exception/JIllegalArgumentException.cpp \
    src/main/cpp/jcpp/lang/JStackTraceElement.cpp \
    src/main/cpp/jcpp/lang/exception/JThrowable.cpp \
    src/main/cpp/jcpp/lang/exception/JRuntimeException.cpp \
    src/main/cpp/jcpp/lang/exception/JError.cpp \
    src/main/cpp/jcpp/lang/exception/JVirtualMachineError.cpp \
    src/main/cpp/jcpp/lang/exception/JInternalError.cpp \
    src/main/cpp/jcpp/lang/exception/JIllegalStateException.cpp \
    src/main/cpp/jcpp/lang/exception/JUnsupportedOperationException.cpp \
    src/main/cpp/jcpp/lang/exception/JClassCastException.cpp \
    src/main/cpp/jcpp/lang/JInterface.cpp \
    src/main/cpp/jcpp/lang/reflect/JAccessibleObject.cpp \
    src/main/cpp/jcpp/lang/reflect/JPackage.cpp \
    src/main/cpp/jcpp/lang/JVoid.cpp \
    src/main/cpp/jcpp/lang/JLANG.cpp \
    src/main/cpp/jcpp/lang/reflect/JREFLECT.cpp \
    src/main/cpp/jcpp/lang/JRunnable.cpp \
    src/main/cpp/jcpp/lang/JThread.cpp \
    src/main/cpp/jcpp/lang/QObjectAware.cpp \
    src/main/cpp/jcpp/lang/JSystem.cpp \
    src/main/cpp/jcpp/lang/QObjectHolder.cpp \
    src/main/cpp/jcpp/lang/exception/JArrayIndexOutOfBoundsException.cpp \
    src/main/cpp/jcpp/lang/JIterable.cpp \
    src/main/cpp/jcpp/lang/JCloneable.cpp \
    src/main/cpp/jcpp/lang/exception/JCloneNotSupportedException.cpp \
    src/main/cpp/jcpp/lang/JComparable.cpp \
    src/main/cpp/jcpp/lang/JThreadLocal.cpp \
    src/main/cpp/jcpp/lang/reflect/JMember.cpp \
    src/main/cpp/jcpp/lang/reflect/JModifier.cpp \
    src/main/cpp/jcpp/lang/JAutoCloseable.cpp \
    src/main/cpp/jcpp/lang/JAppendable.cpp \
    src/main/cpp/jcpp/lang/JCharSequence.cpp \
    src/main/cpp/jcpp/lang/JStringBuilder.cpp \
    src/main/cpp/jcpp/lang/JStringBuffer.cpp \
    src/main/cpp/jcpp/lang/JAbstractStringBuilder.cpp \
    src/main/cpp/jcpp/lang/JReadable.cpp \
    src/main/cpp/jcpp/io/JSerializable.cpp \
    src/main/cpp/jcpp/io/JInputStream.cpp \
    src/main/cpp/jcpp/io/JDataInputStream.cpp \
    src/main/cpp/jcpp/io/QtDataInputStream.cpp \
    src/main/cpp/jcpp/io/JObjectStreamClass.cpp \
    src/main/cpp/jcpp/io/JObjectInputStream.cpp \
    src/main/cpp/jcpp/io/JUTFDataFormatException.cpp \
    src/main/cpp/jcpp/io/JIOException.cpp \
    src/main/cpp/jcpp/io/JEOFException.cpp \
    src/main/cpp/jcpp/io/impl/SerialCallbackContext.cpp \
    src/main/cpp/jcpp/io/impl/HandleTable.cpp \
    src/main/cpp/jcpp/io/impl/HandleList.cpp \
    src/main/cpp/jcpp/io/JObjectStreamException.cpp \
    src/main/cpp/jcpp/io/JInvalidClassException.cpp \
    src/main/cpp/jcpp/io/JStreamCorruptedException.cpp \
    src/main/cpp/jcpp/io/JOptionalDataException.cpp \
    src/main/cpp/jcpp/io/JNotActiveException.cpp \
    src/main/cpp/jcpp/io/JOutputStream.cpp \
    src/main/cpp/jcpp/io/JDataOutputStream.cpp \
    src/main/cpp/jcpp/io/impl/OutputHandleTable.cpp \
    src/main/cpp/jcpp/io/JObjectOutputStream.cpp \
    src/main/cpp/jcpp/io/JObjectStreamField.cpp \
    src/main/cpp/jcpp/io/JExternalizable.cpp \
    src/main/cpp/jcpp/io/JNotSerializableException.cpp \
    src/main/cpp/jcpp/io/QtDataOutputStream.cpp \
    src/main/cpp/jcpp/io/JIO.cpp \
    src/main/cpp/jcpp/io/JWriter.cpp \
    src/main/cpp/jcpp/io/JStringWriter.cpp \
    src/main/cpp/jcpp/io/JBufferedWriter.cpp \
    src/main/cpp/jcpp/io/JByteArrayInputStream.cpp \
    src/main/cpp/jcpp/io/JByteArrayOutputStream.cpp \
    src/main/cpp/jcpp/io/JCharArrayWriter.cpp \
    src/main/cpp/jcpp/io/JOutputStreamWriter.cpp \
    src/main/cpp/jcpp/io/JStringBufferInputStream.cpp \
    src/main/cpp/jcpp/io/JSequenceInputStream.cpp \
    src/main/cpp/jcpp/io/JSerializablePermission.cpp \
    src/main/cpp/jcpp/io/JPushbackInputStream.cpp \
    src/main/cpp/jcpp/io/JPipedOutputStream.cpp \
    src/main/cpp/jcpp/io/JPipedInputStream.cpp \
    src/main/cpp/jcpp/io/JReader.cpp \
    src/main/cpp/jcpp/io/JStringReader.cpp \
    src/main/cpp/jcpp/io/JFilterWriter.cpp \
    src/main/cpp/jcpp/io/JFilterReader.cpp \
    src/main/cpp/jcpp/io/JBufferedReader.cpp \
    src/main/cpp/jcpp/io/JCharArrayReader.cpp \
    src/main/cpp/jcpp/io/JPushbackReader.cpp \
    src/main/cpp/jcpp/io/JPipedWriter.cpp \
    src/main/cpp/jcpp/io/JPipedReader.cpp \
    src/main/cpp/jcpp/io/JInputStreamReader.cpp \
    src/main/cpp/jcpp/io/JLineNumberReader.cpp \
    src/main/cpp/jcpp/io/JFile.cpp \
    src/main/cpp/jcpp/io/JFileFilter.cpp \
    src/main/cpp/jcpp/io/JFilenameFilter.cpp \
    src/main/cpp/jcpp/io/JIOFileSystem.cpp \
    src/main/cpp/jcpp/io/JFileOutputStream.cpp \
    src/main/cpp/jcpp/io/JFileInputStream.cpp \
    src/main/cpp/jcpp/io/JFileWriter.cpp \
    src/main/cpp/jcpp/io/JFileReader.cpp \
    src/main/cpp/jcpp/io/JDefaultFileSystem.cpp \
    src/main/cpp/jcpp/io/JWinNTFileSystem.cpp \
    src/main/cpp/jcpp/io/JObjectStreamConstants.cpp \
    src/main/cpp/jcpp/io/JFilterInputStream.cpp \
    src/main/cpp/jcpp/io/JFilterOutputStream.cpp \
    src/main/cpp/jcpp/io/JBufferedInputStream.cpp \
    src/main/cpp/jcpp/io/JBufferedOutputStream.cpp \
    src/main/cpp/jcpp/io/JInvalidObjectException.cpp \
    src/main/cpp/jcpp/io/impl/JBlockDataInputStream.cpp \
    src/main/cpp/jcpp/io/impl/JBlockDataOutputStream.cpp \
    src/main/cpp/jcpp/io/JDataInput.cpp \
    src/main/cpp/jcpp/io/JDataOutput.cpp \
    src/main/cpp/jcpp/io/JObjectInput.cpp \
    src/main/cpp/jcpp/io/JObjectOutput.cpp \
    src/main/cpp/jcpp/io/JBits.cpp \
    src/main/cpp/jcpp/io/JFlushable.cpp \
    src/main/cpp/jcpp/io/JCloseable.cpp \
    src/main/cpp/jcpp/io/JObjectInputValidation.cpp \
    src/main/cpp/jcpp/io/JIOError.cpp \
    src/main/cpp/jcpp/io/JWriteAbortedException.cpp \
    src/main/cpp/jcpp/io/JUnsupportedEncodingException.cpp \
    src/main/cpp/jcpp/io/JSyncFailedException.cpp \
    src/main/cpp/jcpp/io/JInterruptedIOException.cpp \
    src/main/cpp/jcpp/io/JFileNotFoundException.cpp \
    src/main/cpp/jcpp/io/JCharConversionException.cpp \
    src/main/cpp/jcpp/util/JArrayList.cpp \
    src/main/cpp/jcpp/util/JHashtable.cpp \
    src/main/cpp/jcpp/util/JUTIL.cpp \
    src/main/cpp/jcpp/util/JCollection.cpp \
    src/main/cpp/jcpp/util/JList.cpp \
    src/main/cpp/jcpp/util/JAbstractCollection.cpp \
    src/main/cpp/jcpp/util/JAbstractList.cpp \
    src/main/cpp/jcpp/util/concurrent/JExecutor.cpp \
    src/main/cpp/jcpp/util/concurrent/JCallable.cpp \
    src/main/cpp/jcpp/util/concurrent/JExecutorService.cpp \
    src/main/cpp/jcpp/util/concurrent/JFuture.cpp \
    src/main/cpp/jcpp/util/concurrent/JRunnableFuture.cpp \
    src/main/cpp/jcpp/util/concurrent/JAbstractExecutorService.cpp \
    src/main/cpp/jcpp/util/concurrent/JThreadPoolExecutor.cpp \
    src/main/cpp/jcpp/util/concurrent/JFutureTask.cpp \
    src/main/cpp/jcpp/util/concurrent/JDelayed.cpp \
    src/main/cpp/jcpp/util/concurrent/JScheduledFuture.cpp \
    src/main/cpp/jcpp/util/concurrent/JScheduledExecutorService.cpp \
    src/main/cpp/jcpp/util/concurrent/JScheduledThreadPoolExecutor.cpp \
    src/main/cpp/jcpp/util/concurrent/JCONCURRENT.cpp \
    src/main/cpp/jcpp/util/JTimerTask.cpp \
    src/main/cpp/jcpp/util/JTimer.cpp \
    src/main/cpp/jcpp/util/concurrent/JRunnableScheduledFuture.cpp \
    src/main/cpp/jcpp/util/concurrent/JScheduledFutureTask.cpp \
    src/main/cpp/jcpp/util/JIterator.cpp \
    src/main/cpp/jcpp/util/JListIterator.cpp \
    src/main/cpp/jcpp/util/JRandomAccess.cpp \
    src/main/cpp/jcpp/util/JNoSuchElementException.cpp \
    src/main/cpp/jcpp/util/JConcurrentModificationException.cpp \
    src/main/cpp/jcpp/util/JVector.cpp \
    src/main/cpp/jcpp/util/JEnumeration.cpp \
    src/main/cpp/jcpp/util/JCollections.cpp \
    src/main/cpp/jcpp/util/JSet.cpp \
    src/main/cpp/jcpp/util/JAbstractSet.cpp \
    src/main/cpp/jcpp/util/JHashSet.cpp \
    src/main/cpp/jcpp/util/JMap.cpp \
    src/main/cpp/jcpp/util/JAbstractMap.cpp \
    src/main/cpp/jcpp/util/JHashMap.cpp \
    src/main/cpp/jcpp/util/JDictionary.cpp \
    src/main/cpp/jcpp/util/JComparator.cpp \
    src/main/cpp/jcpp/util/JQueue.cpp \
    src/main/cpp/jcpp/util/JAbstractQueue.cpp \
    src/main/cpp/jcpp/util/JIdentityHashMap.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JAddress.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JRoute.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayInputStream.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayOutputStream.cpp \
    src/main/cpp/jcpp/rmi/JRMI.cpp \
    src/main/cpp/jcpp/rmi/server/impl/JIMPL.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGATEWAY.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JEndPoint.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JITransportRouter.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTransportRouter.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JConnection.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JConnections.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTRANSPORT_PACKAGE.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTransport.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JITransportDispatcher.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JConnectionHeaderReader.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayConfiguration.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewaySocketFactory.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JIGatewaySocket.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewaySocket.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayServerSocket.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayCompressionInputStream.cpp \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayCompressionOutputStream.cpp \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTransportConfiguration.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectPointer.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionConfiguration.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionException.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCClient.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCClientListener.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIInvocationExceptionHandler.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIInvocationListener.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JILifecycle.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JINotExportedObjectListener.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JINotSerializableObjectHandler.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JDefaultNotSerializableObjectHandler.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JNullNotSerializableObjectHandler.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIRegistry.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIServer.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectInformation.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectHandler.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectInformations.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JRegistry.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JServer.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JInvoker.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionInputStream.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionOutputStream.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGC.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGCClient.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGCEndPointInfo.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGCClientEndPointInfo.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionTransportDispatcher.cpp \
    src/main/cpp/jcpp/rmi/server/JSERVER_PACKAGE.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JMethodDigester.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JCONNECTION_PACKAGE.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JCONNECTION_SERIALIZATION_PACKAGE.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIRegistryProxy.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCProxy.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCClientProxy.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIServerProxy.cpp \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGC.cpp \
    src/main/cpp/jcpp/net/JInetAddress.cpp \
    src/main/cpp/jcpp/net/JSocket.cpp \
    src/main/cpp/jcpp/net/JNET.cpp \
    src/main/cpp/jcpp/net/JServerSocket.cpp \
    src/main/cpp/jcpp/net/JInet4Address.cpp \
    src/main/cpp/jcpp/net/JInet6Address.cpp \
    src/main/cpp/jcpp/net/JURLClassLoader.cpp \
    src/main/cpp/jcpp/JCPP_PACKAGE.cpp \
    src/main/cpp/jcpp/security/MD5.cpp \
    src/main/cpp/jcpp/security/JSecureClassLoader.cpp \
    src/main/cpp/jcpp/security/JGuard.cpp \
    src/main/cpp/jcpp/security/JSECURITY_PACKAGE.cpp \
    src/main/cpp/jcpp/security/JPermission.cpp \
    src/main/cpp/jcpp/security/JPermissionCollection.cpp \
    src/main/cpp/jcpp/security/JBasicPermission.cpp \
    src/main/cpp/jcpp/nio/JNIO_PACKAGE.cpp \
    src/main/cpp/jcpp/nio/file/JNIO_FILE_PACKAGE.cpp \
    src/main/cpp/jcpp/nio/file/JWatchEvent.cpp \
    src/main/cpp/jcpp/nio/file/JWatchable.cpp \
    src/main/cpp/jcpp/nio/file/JWatchService.cpp \
    src/main/cpp/jcpp/nio/file/JWatchKey.cpp \
    src/main/cpp/jcpp/nio/file/JOpenOption.cpp \
    src/main/cpp/jcpp/nio/file/JCopyOption.cpp \
    src/main/cpp/jcpp/nio/file/JDirectoryStream.cpp \
    src/main/cpp/jcpp/nio/file/JFileSystemException.cpp \
    src/main/cpp/jcpp/nio/file/JAccessDeniedException.cpp \
    src/main/cpp/jcpp/nio/file/JAtomicMoveNotSupportedException.cpp \
    src/main/cpp/jcpp/nio/file/JClosedDirectoryStreamException.cpp \
    src/main/cpp/jcpp/nio/file/JClosedFileSystemException.cpp \
    src/main/cpp/jcpp/nio/file/JClosedWatchServiceException.cpp \
    src/main/cpp/jcpp/nio/file/JDirectoryNotEmptyException.cpp \
    src/main/cpp/jcpp/nio/file/JFileAlreadyExistsException.cpp \
    src/main/cpp/jcpp/nio/file/JFileSystemAlreadyExistsException.cpp \
    src/main/cpp/jcpp/nio/file/JFileSystemLoopException.cpp \
    src/main/cpp/jcpp/nio/file/JFileSystemNotFoundException.cpp \
    src/main/cpp/jcpp/nio/file/JNoSuchFileException.cpp \
    src/main/cpp/jcpp/nio/file/JNotDirectoryException.cpp \
    src/main/cpp/jcpp/nio/file/JNotLinkException.cpp \
    src/main/cpp/jcpp/nio/file/JProviderMismatchException.cpp \
    src/main/cpp/jcpp/nio/file/JProviderNotFoundException.cpp \
    src/main/cpp/jcpp/nio/file/JReadOnlyFileSystemException.cpp \
    src/main/cpp/jcpp/nio/file/JDirectoryIteratorException.cpp \
    src/main/cpp/jcpp/nio/file/JInvalidPathException.cpp \
    src/main/cpp/jcpp/nio/file/JAccessMode.cpp \
    src/main/cpp/jcpp/nio/file/JFileVisitOption.cpp \
    src/main/cpp/jcpp/nio/file/JFileVisitResult.cpp \
    src/main/cpp/jcpp/nio/file/JLinkOption.cpp \
    src/main/cpp/jcpp/nio/file/JStandardOpenOption.cpp \
    src/main/cpp/jcpp/nio/file/JStandardCopyOption.cpp \
    src/main/cpp/jcpp/nio/file/JSecureDirectoryStream.cpp \
    src/main/cpp/jcpp/nio/file/JFileVisitor.cpp \
    src/main/cpp/jcpp/nio/file/JFileSystem.cpp \
    src/main/cpp/jcpp/nio/file/JPathMatcher.cpp \
    src/main/cpp/jcpp/nio/file/JPath.cpp \
    src/main/cpp/jcpp/util/logging/JLOGGING_PACKAGE.cpp \
    src/main/cpp/jcpp/util/logging/JLevel.cpp \
    src/main/cpp/jcpp/util/logging/JLogRecord.cpp \
    src/main/cpp/jcpp/util/logging/JFilter.cpp \
    src/main/cpp/jcpp/util/logging/JErrorManager.cpp \
    src/main/cpp/jcpp/util/logging/JFormatter.cpp \
    src/main/cpp/jcpp/util/logging/JHandler.cpp \
    src/main/cpp/jcpp/util/logging/JLogManager.cpp \
    src/main/cpp/jcpp/util/logging/JLogger.cpp \
    src/main/cpp/jcpp/util/logging/JStreamHandler.cpp \
    src/main/cpp/jcpp/util/logging/JSimpleFormatter.cpp \
    src/main/cpp/jcpp/util/logging/JXMLFormatter.cpp \
    src/main/cpp/jcpp/util/logging/JSocketHandler.cpp \
    src/main/cpp/jcpp/util/logging/JMemoryHandler.cpp \
    src/main/cpp/jcpp/util/logging/JConsoleHandler.cpp
    
    
HEADERS += \
    src/main/cpp/jcpp/lang/JClass.h \
    src/main/cpp/jcpp/lang/JClassLoader.h \
    src/main/cpp/jcpp/lang/JObject.h \
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
    src/main/cpp/jcpp/io/JObjectStreamException.h \
    src/main/cpp/jcpp/io/JInvalidClassException.h \
    src/main/cpp/jcpp/lang/exception/JError.h \
    src/main/cpp/jcpp/lang/exception/JVirtualMachineError.h \
    src/main/cpp/jcpp/lang/exception/JInternalError.h \
    src/main/cpp/jcpp/io/JStreamCorruptedException.h \
    src/main/cpp/jcpp/io/JOptionalDataException.h \
    src/main/cpp/jcpp/io/JNotActiveException.h \
    src/main/cpp/jcpp/io/JIO.h \
    src/main/cpp/jcpp/lang/exception/JIllegalStateException.h \
    src/main/cpp/jcpp/lang/exception/JUnsupportedOperationException.h \
    src/main/cpp/jcpp/lang/exception/JClassCastException.h \
    src/main/cpp/jcpp/io/JOutputStream.h \
    src/main/cpp/jcpp/io/JDataOutputStream.h \
    src/main/cpp/jcpp/io/impl/OutputHandleTable.h \
    src/main/cpp/jcpp/io/JObjectOutputStream.h \
    src/main/cpp/jcpp/io/JObjectStreamField.h \
    src/main/cpp/jcpp/lang/JVoid.h \
    src/main/cpp/jcpp/io/JExternalizable.h \
    src/main/cpp/jcpp/io/JNotSerializableException.h \
    src/main/cpp/jcpp/io/QtDataOutputStream.h \
    src/main/cpp/jcpp/lang/Object.h \
    src/main/cpp/jcpp/lang/JInterface.h \
    src/main/cpp/jcpp/lang/reflect/JAccessibleObject.h \
    src/main/cpp/jcpp/lang/reflect/JPackage.h \
    src/main/cpp/jcpp/lang/JLANG.h \
    src/main/cpp/jcpp/lang/reflect/JREFLECT.h \
    src/main/cpp/jcpp/util/JUTIL.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JAddress.h \
    src/main/cpp/jcpp/util/JAbstractList.h \
    src/main/cpp/jcpp/util/JList.h \
    src/main/cpp/jcpp/util/JAbstractCollection.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JRoute.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayInputStream.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayOutputStream.h \
    src/main/cpp/jcpp/net/JSocket.h \
    src/main/cpp/jcpp/net/JInetAddress.h \
    src/main/cpp/jcpp/net/JNET.h \
    src/main/cpp/jcpp/rmi/JRMI.h \
    src/main/cpp/jcpp/rmi/server/impl/JIMPL.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGATEWAY.h \
    src/main/cpp/jcpp/net/JServerSocket.h \
    src/main/cpp/jcpp/lang/JThread.h \
    src/main/cpp/jcpp/lang/JRunnable.h \
    src/main/cpp/jcpp/lang/QObjectAware.h \
    src/main/cpp/jcpp/net/JInet4Address.h \
    src/main/cpp/jcpp/net/JInet6Address.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JEndPoint.h \
    src/main/cpp/jcpp/util/concurrent/JExecutor.h \
    src/main/cpp/jcpp/util/concurrent/JExecutorService.h \
    src/main/cpp/jcpp/util/concurrent/JFuture.h \
    src/main/cpp/jcpp/util/concurrent/JRunnableFuture.h \
    src/main/cpp/jcpp/util/concurrent/JCallable.h \
    src/main/cpp/jcpp/util/concurrent/JAbstractExecutorService.h \
    src/main/cpp/jcpp/util/concurrent/JThreadPoolExecutor.h \
    src/main/cpp/jcpp/util/concurrent/JFutureTask.h \
    src/main/cpp/jcpp/util/concurrent/JDelayed.h \
    src/main/cpp/jcpp/util/concurrent/JScheduledFuture.h \
    src/main/cpp/jcpp/util/concurrent/JScheduledExecutorService.h \
    src/main/cpp/jcpp/util/concurrent/JScheduledThreadPoolExecutor.h \
    src/main/cpp/jcpp/util/concurrent/JCONCURRENT.h \
    src/main/cpp/jcpp/util/JTimer.h \
    src/main/cpp/jcpp/util/JTimerTask.h \
    src/main/cpp/jcpp/lang/JSystem.h \
    src/main/cpp/jcpp/util/concurrent/JRunnableScheduledFuture.h \
    src/main/cpp/jcpp/util/concurrent/JScheduledFutureTask.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JITransportRouter.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTransportRouter.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JConnection.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JConnections.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTRANSPORT_PACKAGE.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTransport.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JITransportDispatcher.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JConnectionHeaderReader.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewaySocketFactory.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayConfiguration.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JIGatewaySocket.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewaySocket.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayServerSocket.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayCompressionInputStream.h \
    src/main/cpp/jcpp/rmi/server/impl/gateway/JGatewayCompressionOutputStream.h \
    src/main/cpp/jcpp/rmi/server/impl/transport/JTransportConfiguration.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectPointer.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionConfiguration.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionException.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGC.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCClient.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCClientListener.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIInvocationExceptionHandler.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIInvocationListener.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JILifecycle.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JINotExportedObjectListener.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JINotSerializableObjectHandler.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JDefaultNotSerializableObjectHandler.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JNullNotSerializableObjectHandler.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIRegistry.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIServer.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectInformation.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectHandler.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JObjectInformations.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JRegistry.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JServer.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JInvoker.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionInputStream.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionOutputStream.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGC.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGCClient.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGCEndPointInfo.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JGCClientEndPointInfo.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JConnectionTransportDispatcher.h \
    src/main/cpp/jcpp/rmi/server/JSERVER_PACKAGE.h \
    src/main/cpp/jcpp/security/MD5.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JMethodDigester.h \
    src/main/cpp/jcpp/lang/QObjectHolder.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JCONNECTION_PACKAGE.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/serialization/JCONNECTION_SERIALIZATION_PACKAGE.h \
    src/main/cpp/jcpp/JCPP_PACKAGE.h \
    src/main/cpp/jcpp/JCPP.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIRegistryProxy.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCProxy.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIGCClientProxy.h \
    src/main/cpp/jcpp/rmi/server/impl/connection/JIServerProxy.h \
    src/main/cpp/jcpp/io/JFilterInputStream.h \
    src/main/cpp/jcpp/io/JFilterOutputStream.h \
    src/main/cpp/jcpp/io/JBufferedInputStream.h \
    src/main/cpp/jcpp/io/JBufferedOutputStream.h \
    src/main/cpp/jcpp/lang/JIterable.h \
    src/main/cpp/jcpp/util/JIterator.h \
    src/main/cpp/jcpp/util/JListIterator.h \
    src/main/cpp/jcpp/util/JRandomAccess.h \
    src/main/cpp/jcpp/lang/JCloneable.h \
    src/main/cpp/jcpp/util/JNoSuchElementException.h \
    src/main/cpp/jcpp/util/JConcurrentModificationException.h \
    src/main/cpp/jcpp/util/JVector.h \
    src/main/cpp/jcpp/util/JEnumeration.h \
    src/main/cpp/jcpp/lang/exception/JArrayIndexOutOfBoundsException.h \
    src/main/cpp/jcpp/util/JCollections.h \
    src/main/cpp/jcpp/lang/exception/JCloneNotSupportedException.h \
    src/main/cpp/jcpp/lang/JComparable.h \
    src/main/cpp/jcpp/util/JSet.h \
    src/main/cpp/jcpp/util/JAbstractSet.h \
    src/main/cpp/jcpp/util/JHashSet.h \
    src/main/cpp/jcpp/util/JMap.h \
    src/main/cpp/jcpp/util/JAbstractMap.h \
    src/main/cpp/jcpp/util/JHashMap.h \
    src/main/cpp/jcpp/util/JDictionary.h \
    src/main/cpp/jcpp/io/JInvalidObjectException.h \
    src/main/cpp/jcpp/util/JComparator.h \
    src/main/cpp/jcpp/util/JQueue.h \
    src/main/cpp/jcpp/util/JAbstractQueue.h \
    src/main/cpp/jcpp/io/JBits.h \
    src/main/cpp/jcpp/lang/JThreadLocal.h \
    src/main/cpp/jcpp/util/JIdentityHashMap.h \
    src/main/cpp/jcpp/lang/reflect/JMember.h \
    src/main/cpp/jcpp/lang/reflect/JModifier.h \
    src/main/cpp/jcpp/io/impl/JBlockDataInputStream.h \
    src/main/cpp/jcpp/io/impl/JBlockDataOutputStream.h \
    src/main/cpp/jcpp/io/JDataInput.h \
    src/main/cpp/jcpp/io/JDataOutput.h \
    src/main/cpp/jcpp/lang/JAutoCloseable.h \
    src/main/cpp/jcpp/io/JObjectInput.h \
    src/main/cpp/jcpp/io/JObjectOutput.h \
    src/main/cpp/jcpp/io/JFlushable.h \
    src/main/cpp/jcpp/io/JCloseable.h \
    src/main/cpp/jcpp/io/JObjectInputValidation.h \
    src/main/cpp/jcpp/io/JIOError.h \
    src/main/cpp/jcpp/io/JWriteAbortedException.h \
    src/main/cpp/jcpp/io/JUnsupportedEncodingException.h \
    src/main/cpp/jcpp/io/JSyncFailedException.h \
    src/main/cpp/jcpp/io/JInterruptedIOException.h \
    src/main/cpp/jcpp/io/JFileNotFoundException.h \
    src/main/cpp/jcpp/io/JCharConversionException.h \
    src/main/cpp/jcpp/lang/JAppendable.h \
    src/main/cpp/jcpp/lang/JCharSequence.h \
    src/main/cpp/jcpp/io/JWriter.h \
    src/main/cpp/jcpp/io/JStringWriter.h \
    src/main/cpp/jcpp/lang/JStringBuilder.h \
    src/main/cpp/jcpp/lang/JStringBuffer.h \
    src/main/cpp/jcpp/lang/JAbstractStringBuilder.h \
    src/main/cpp/jcpp/io/JBufferedWriter.h \
    src/main/cpp/jcpp/io/JByteArrayInputStream.h \
    src/main/cpp/jcpp/io/JByteArrayOutputStream.h \
    src/main/cpp/jcpp/io/JCharArrayWriter.h \
    src/main/cpp/jcpp/io/JOutputStreamWriter.h \
    src/main/cpp/jcpp/io/JStringBufferInputStream.h \
    src/main/cpp/jcpp/io/JSequenceInputStream.h \
    src/main/cpp/jcpp/security/JGuard.h \
    src/main/cpp/jcpp/security/JSECURITY_PACKAGE.h \
    src/main/cpp/jcpp/security/JPermission.h \
    src/main/cpp/jcpp/security/JPermissionCollection.h \
    src/main/cpp/jcpp/security/JBasicPermission.h \
    src/main/cpp/jcpp/io/JSerializablePermission.h \
    src/main/cpp/jcpp/io/JPushbackInputStream.h \
    src/main/cpp/jcpp/io/JPipedOutputStream.h \
    src/main/cpp/jcpp/io/JPipedInputStream.h \
    src/main/cpp/jcpp/io/JReader.h \
    src/main/cpp/jcpp/lang/JReadable.h \
    src/main/cpp/jcpp/io/JStringReader.h \
    src/main/cpp/jcpp/io/JFilterWriter.h \
    src/main/cpp/jcpp/io/JFilterReader.h \
    src/main/cpp/jcpp/io/JBufferedReader.h \
    src/main/cpp/jcpp/io/JCharArrayReader.h \
    src/main/cpp/jcpp/io/JPushbackReader.h \
    src/main/cpp/jcpp/io/JPipedWriter.h \
    src/main/cpp/jcpp/io/JPipedReader.h \
    src/main/cpp/jcpp/io/JInputStreamReader.h \
    src/main/cpp/jcpp/io/JLineNumberReader.h \
    src/main/cpp/jcpp/nio/JNIO_PACKAGE.h \
    src/main/cpp/jcpp/nio/file/JNIO_FILE_PACKAGE.h \
    src/main/cpp/jcpp/nio/file/JWatchEvent.h \
    src/main/cpp/jcpp/nio/file/JWatchable.h \
    src/main/cpp/jcpp/nio/file/JWatchService.h \
    src/main/cpp/jcpp/nio/file/JWatchKey.h \
    src/main/cpp/jcpp/nio/file/JOpenOption.h \
    src/main/cpp/jcpp/nio/file/JCopyOption.h \
    src/main/cpp/jcpp/nio/file/JDirectoryStream.h \
    src/main/cpp/jcpp/nio/file/JFileSystemException.h \
    src/main/cpp/jcpp/nio/file/JAccessDeniedException.h \
    src/main/cpp/jcpp/nio/file/JAtomicMoveNotSupportedException.h \
    src/main/cpp/jcpp/nio/file/JClosedDirectoryStreamException.h \
    src/main/cpp/jcpp/nio/file/JClosedFileSystemException.h \
    src/main/cpp/jcpp/nio/file/JClosedWatchServiceException.h \
    src/main/cpp/jcpp/nio/file/JDirectoryNotEmptyException.h \
    src/main/cpp/jcpp/nio/file/JFileAlreadyExistsException.h \
    src/main/cpp/jcpp/nio/file/JFileSystemAlreadyExistsException.h \
    src/main/cpp/jcpp/nio/file/JFileSystemLoopException.h \
    src/main/cpp/jcpp/nio/file/JFileSystemNotFoundException.h \
    src/main/cpp/jcpp/nio/file/JNoSuchFileException.h \
    src/main/cpp/jcpp/nio/file/JNotDirectoryException.h \
    src/main/cpp/jcpp/nio/file/JNotLinkException.h \
    src/main/cpp/jcpp/nio/file/JProviderMismatchException.h \
    src/main/cpp/jcpp/nio/file/JProviderNotFoundException.h \
    src/main/cpp/jcpp/nio/file/JReadOnlyFileSystemException.h \
    src/main/cpp/jcpp/nio/file/JDirectoryIteratorException.h \
    src/main/cpp/jcpp/nio/file/JInvalidPathException.h \
    src/main/cpp/jcpp/nio/file/JAccessMode.h \
    src/main/cpp/jcpp/nio/file/JFileVisitOption.h \
    src/main/cpp/jcpp/nio/file/JFileVisitResult.h \
    src/main/cpp/jcpp/nio/file/JLinkOption.h \
    src/main/cpp/jcpp/nio/file/JStandardOpenOption.h \
    src/main/cpp/jcpp/nio/file/JStandardCopyOption.h \
    src/main/cpp/jcpp/nio/file/JSecureDirectoryStream.h \
    src/main/cpp/jcpp/nio/file/JFileVisitor.h \
    src/main/cpp/jcpp/nio/file/JFileSystem.h \
    src/main/cpp/jcpp/nio/file/JPathMatcher.h \
    src/main/cpp/jcpp/nio/file/JPath.h \
    src/main/cpp/jcpp/io/JFile.h \
    src/main/cpp/jcpp/io/JFileFilter.h \
    src/main/cpp/jcpp/io/JFilenameFilter.h \
    src/main/cpp/jcpp/io/JIOFileSystem.h \
    src/main/cpp/jcpp/io/JFileOutputStream.h \
    src/main/cpp/jcpp/io/JFileInputStream.h \
    src/main/cpp/jcpp/io/JFileWriter.h \
    src/main/cpp/jcpp/io/JFileReader.h \
    src/main/cpp/jcpp/lang/reflect/JIPackageLoader.h \
    src/main/cpp/jcpp/security/JSecureClassLoader.h \
    src/main/cpp/jcpp/net/JURLClassLoader.h \
    src/main/cpp/jcpp/io/JDefaultFileSystem.h \
    src/main/cpp/jcpp/io/JWinNTFileSystem.h \
    src/main/cpp/jcpp/util/logging/JLOGGING_PACKAGE.h \
    src/main/cpp/jcpp/util/logging/JLevel.h \
    src/main/cpp/jcpp/util/logging/JLogRecord.h \
    src/main/cpp/jcpp/util/logging/JFilter.h \
    src/main/cpp/jcpp/util/logging/JErrorManager.h \
    src/main/cpp/jcpp/util/logging/JFormatter.h \
    src/main/cpp/jcpp/util/logging/JHandler.h \
    src/main/cpp/jcpp/util/logging/JLogManager.h \
    src/main/cpp/jcpp/util/logging/JLogger.h \
    src/main/cpp/jcpp/util/logging/JStreamHandler.h \
    src/main/cpp/jcpp/util/logging/JSimpleFormatter.h \
    src/main/cpp/jcpp/util/logging/JXMLFormatter.h \
    src/main/cpp/jcpp/util/logging/JSocketHandler.h \
    src/main/cpp/jcpp/util/logging/JMemoryHandler.h \
    src/main/cpp/jcpp/util/logging/JConsoleHandler.h
    
    
OTHER_FILES += \
    todo.txt
