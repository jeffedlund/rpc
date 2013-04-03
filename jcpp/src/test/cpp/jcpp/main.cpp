#include "JClass.h"
#include "JDouble.h"
#include <iostream>
#include "JIO.h"
#include "QtDataInputStream.h"
#include "JSampleObject.h"
#include <QFile>
#include <QString>
#include <QDataStream>
#include <map>
#include "JThrowable.h"
#include "QtDataOutputStream.h"
#include "JThrowableTest.h"
#include "JTest.h"
#include "JErrorTest.h"
#include "JExceptionTest.h"
#include "JRuntimeExceptionTest.h"
#include "JClassCastExceptionTest.h"
#include "JClassNotFoundExceptionTest.h"
#include "JIllegalArgumentExceptionTest.h"
#include "JIllegalStateExceptionTest.h"
#include "JIndexOutOfBoundsExceptionTest.h"
#include "JInstantiationExceptionTest.h"
#include "JVirtualMachineErrorTest.h"
#include "JInternalErrorTest.h"
#include "JNoSuchFieldExceptionTest.h"
#include "JNoSuchMethodExceptionTest.h"
#include "JNullPointerExceptionTest.h"
#include "JUnsupportedOperationExceptionTest.h"
#include "JIOExceptionTest.h"
#include "JObjectStreamExceptionTest.h"
#include "JInvalidClassExceptionTest.h"
#include "JNotActiveExceptionTest.h"
#include "JNotSerializableExceptionTest.h"
#include "JOptionalDataExceptionTest.h"
#include "JStreamCorruptedExceptionTest.h"
#include "JUTFDataFormatExceptionTest.h"
#include "JObjectStreamExceptionTest.h"
#include "JShortTest.h"
#include "JBooleanTest.h"
#include "JByteTest.h"
#include "JCharTest.h"
#include "JDoubleTest.h"
#include "JFloatTest.h"
#include "JIntegerTest.h"
#include "JLongTest.h"
#include "JStringTest.h"
#include "JPrimitiveBooleanTest.h"
#include "JPrimitiveByteTest.h"
#include "JPrimitiveCharTest.h"
#include "JPrimitiveDoubleTest.h"
#include "JPrimitiveFloatTest.h"
#include "JPrimitiveLongTest.h"
#include "JPrimitiveShortTest.h"
#include "JPrimitiveIntTest.h"
#include "JArrayListTest.h"
#include "JSocket.h"
#include "JServerSocket.h"
#include "JThread.h"
#include "QCoreApplication"
#include "JTimerTask.h"
#include "JTimer.h"
#include "JSystem.h"
#include "JScheduledExecutorService.h"
#include "JScheduledFutureTask.h"
#include "JTransport.h"
#include "JITransportDispatcher.h"
#include "JServer.h"
#include "JTransportRouter.h"
#include "JProxy.h"
#include "JBitsTest.h"
#include "JServerTest.h"
#include "JSerializableTest.h"
#include "JExternalizableTest.h"
#include "JExternalizableObject.h"
#include "JHashMapTest.h"
#include "JHashSetTest.h"
#include "JHashtableTest.h"
#include "JIdentityHashMapTest.h"
#include "JPrimitiveArrayTest.h"
using namespace std;
using namespace jcpp::util;
using namespace jcpp::lang;
using namespace jcpp;
using namespace jcpp::net;
using namespace jcpp::util::concurrent;
using namespace jcpp::rmi::server::impl::transport;
using namespace jcpp::rmi::server::impl::gateway;
using namespace jcpp::rmi::server::impl::connection;

static int TEST_SIZE = 51;
static JTest* tests[] = {new JThrowableTest(),new JErrorTest(),new JExceptionTest(),new JRuntimeExceptionTest(),
                         new JClassCastExceptionTest(),new JClassNotFoundExceptionTest(),new JIllegalArgumentExceptionTest(),
                         new JIllegalStateExceptionTest(),new JIndexOutOfBoundsExceptionTest(),new JInstantiationExceptionTest(),
                         new JVirtualMachineErrorTest(),new JInternalErrorTest(),new JNoSuchFieldExceptionTest(),
                         new JNoSuchMethodExceptionTest(),new JNullPointerExceptionTest(),new JUnsupportedOperationExceptionTest(),
                         new JIOExceptionTest(),new JObjectStreamExceptionTest(),new JInvalidClassExceptionTest(),
                         new JNotActiveExceptionTest(),new JNotSerializableExceptionTest(),new JOptionalDataExceptionTest(),
                         new JStreamCorruptedExceptionTest(),new JUTFDataFormatExceptionTest(),new JObjectStreamExceptionTest(),
                         new JShortTest(),new JBooleanTest(),new JByteTest(),new JCharTest(),new JDoubleTest(),
                         new JFloatTest(),new JIntegerTest(),new JLongTest(),new JStringTest(),
                         new JPrimitiveBooleanTest(),new JPrimitiveByteTest(),new JPrimitiveCharTest(),
                         new JPrimitiveDoubleTest(),new JPrimitiveFloatTest(),new JPrimitiveLongTest(),
                         new JPrimitiveShortTest(),new JPrimitiveIntTest(),new JArrayListTest(),
                         new JSerializableTest,new JExternalizableTest,new JHashMapTest,
                         new JHashSetTest,new JIdentityHashMapTest, new JHashtableTest,
                         new JPrimitiveArrayTest,new JServerTest};

void registerClasses(){
    JClassLoader::getBootClassLoader()->addClass(JSampleObject::getClazz());
    JClassLoader::getBootClassLoader()->addClass(JExternalizableObject::getClazz());
}

void testException(){
    try{
        JThrowable* t=new JThrowable();
        t->setMessage(new JString("throwable"));

        JException* te=new JException();
        te->setMessage(new JString("exception"));

        JIllegalArgumentException* tia=new JIllegalArgumentException;
        tia->setMessage(new JString("illegal exception"));

        throw tia;
    }catch(JIllegalArgumentException* t3){
        t3->printStackTrace(&cout);
    }catch(JException* t1){
        t1->printStackTrace(&cout);
    }catch(JThrowable* t2){
        t2->printStackTrace(&cout);
    }
}

int main(int argc, char *argv[]){
    QCoreApplication  a(argc,argv);

    //TODO should be done by default ...
    registerClasses();
    testException();

    for (int i=0;i<TEST_SIZE;i++){
        cout<<"testing in file"<<tests[i]->getFileName();
        cout.flush();
        tests[i]->test();
        cout<<"end testing in file"<<tests[i]->getFileName();
        cout.flush();
    }

    return a.exec();
}

