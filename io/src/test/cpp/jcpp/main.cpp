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
using namespace std;
using namespace jcpp::util;
using namespace jcpp::lang;
using namespace jcpp;
using namespace jcpp::net;

static int TEST_SIZE = 43;
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
                         new JPrimitiveShortTest(),new JPrimitiveIntTest(),new JArrayListTest()};

void registerClasses(){
    JClassLoader::getBootClassLoader()->addClass(JSampleObject::getClazz());
}

/*TODO have test cases for input stream:
  1-primitive arrays of primitive type
  2-primitive arrays of object
  3-primitive array of primitive array
  4-object of object of object
  5-object containing proxy
*/
JSampleObject* testReadSampleObject(){
    try{
        QString name("E:\\project\\rpc\\io\\src\\main\\java\\output.b");
        QFile* file=new QFile(name);
        file->open(QIODevice::ReadOnly);
        QDataStream* qs=new QDataStream(file);
        QtDataInputStream* qis=new QtDataInputStream(qs);
        JObjectInputStream* ois=new JObjectInputStream(qis);
        JSampleObject* sample=(JSampleObject*)ois->readObject();
        cout<<sample->toString();
        return sample;
    }catch(JThrowable* thr){
        cout<<thr->toString();
        throw thr;
    }
}

void testWriteSampleObject(JSampleObject* sample){
    QString name("E:\\project\\rpc\\io\\src\\main\\java\\output2.b");
    QFile* file=new QFile(name);
    file->open(QIODevice::WriteOnly);
    QDataStream* qs=new QDataStream(file);
    QtDataOutputStream* qos=new QtDataOutputStream(qs,file);
    JObjectOutputStream* oos=new JObjectOutputStream(qos);
    oos->writeObject(sample);
    file->close();
}

void testMap(){
    std::map<string,int> mymap;
    mymap["sample"]=30;
    mymap["c5"]=40;
    map<string,int>::const_iterator i = mymap.find("c");
    if (i!=mymap.end()){
        cout<<(*i).second;
    }else{
        cout<<"not found";
    }
    i = mymap.find("c4");
    if (i!=mymap.end()){
        cout<<(*i).second;
    }else{
        cout<<"not found";
    }
    i = mymap.find("c5");
    if (i!=mymap.end()){
        cout<<(*i).second;
    }else{
        cout<<"not found";
    }
    i = mymap.find("sample");
    if (i!=mymap.end()){
        cout<<(*i).second;
    }else{
        cout<<"not found";
    }
}

class ServerSocketRunnable : public JRunnable{

public:
    JServerSocket* server;
    ServerSocketRunnable(string host, int port){
        this->server=new JServerSocket(new JString(host), new JPrimitiveInt(port),new JPrimitiveInt(200));
        server->connect();
    }

    void run(){
        JSocket* socket=server->accept();
        JObjectOutputStream* oos=new JObjectOutputStream(socket->getOutputStream());
        JObjectInputStream* ois=new JObjectInputStream(socket->getInputStream());
        while (true){
            cout<<"before reading \r\n";
            cout.flush();
            JObject* obj=ois->readObject();
            cout<<obj->toString();
            cout.flush();
            cout<<"after reading \r\n";
            cout.flush();

            cout<<"before writing \r\n";
            cout.flush();
            oos->writeObject(obj);
            cout<<"after writing \r\n";
            cout.flush();
            //JThread::sleep(1000);
        }
    }
};

class ClientSocketRunnable : public JRunnable{
public:
    JSocket* socket;
    ClientSocketRunnable(string host,int port){
        JThread::sleep(5);
        this->socket=new JSocket(new JString(host),new JPrimitiveInt(port));
    }

    void run(){
        JObjectOutputStream* oos=new JObjectOutputStream(socket->getOutputStream());
        JObjectInputStream* ois=new JObjectInputStream(socket->getInputStream());
        while (true){
            cout<<"before writing \r\n";
            cout.flush();
            oos->writeObject(new JString("hello "));
            oos->flush();
            cout<<"after writing \r\n";
            cout.flush();

            cout<<"before reading \r\n";
            cout.flush();
            JObject* obj=ois->readObject();
            cout<<obj->toString();
            cout.flush();
            cout<<"after reading \r\n";
            cout.flush();
            JThread::sleep(1);
        }
    }
};

void testSocket(){
    ServerSocketRunnable* ssr=new ServerSocketRunnable("localhost",12345);
    JThread* th=new JThread(ssr);
    th->move(ssr->server);
    th->start();
    ClientSocketRunnable* csr=new ClientSocketRunnable("localhost",12345);
    JThread* th2=new JThread(csr);
    th2->move(csr->socket);
    th2->start();
    JThread::sleep(100000);
}

class PrintRunnable : public JRunnable{
    void run(){
        for (int i=0;i<100;i++){
            cout<<"wait de "<<i;
            JThread::sleep(1);
        }
    }
};

void testThread(){
    JThread* th=new JThread(new PrintRunnable);
    th->start();
    cout<<"Thread a ete cree";
    JThread::sleep(600000000);
}

int main(int argc, char *argv[]){
    QCoreApplication  a(argc,argv);

    //TODO should be done by default ...
    registerClasses();

    testSocket();

    //testThread();

//    for (int i=0;i<TEST_SIZE;i++){
//        cout<<"testing in file"<<tests[i]->getFileName();
//        cout.flush();
//        tests[i]->test();
//        cout<<"end testing in file"<<tests[i]->getFileName();
//        cout.flush();
//    }

    //testMap();
//    JSampleObject* sample=testReadSampleObject();
//    testWriteSampleObject(sample);

//    JObject object;
//    cout<<object.toString();
//    string str;
//    cin>>str;
//    cout<<object.getClass()->getSerialVersionUID();
//    cin>>str;
//    JDouble* jd=new JDouble(45);
//    cout<<jd->toString();
//    cin>>str;
//    cout<<jd->getClass()->getSerialVersionUID();
//    cout<<"clazz=="<<JClass::getClazz()->getName();
//    cout<<"jdouble class=="<<jd->getClass()->getName();
//    cout<<"jdouble class.class=="<<jd->getClass()->getClass()->getName();
//    cin>>str;
    return a.exec();
}

