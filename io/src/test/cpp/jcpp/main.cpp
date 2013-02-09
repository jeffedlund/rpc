#include "JClass.h"
#include "JDouble.h"
#include <iostream>
#include "JIO.h"
#include "QtDataInputStream.h"
#include "JSampleObject.h"
#include <QtGlobal>
#include <QFile>
#include <QString>
#include <QDataStream>
#include <map>
#include "JBootClassBuilder.h"
#include "JThrowable.h"
#include "QtDataOutputStream.h"
#include "JThrowableTest.h"

using namespace std;


class JSampleClassBuilder : public JClassBuilder{
    vector<JClass*> * classes;

public :
    JSampleClassBuilder(){
        classes=new vector<JClass*>();
        classes->push_back(JSampleObject::getClazz());
    }

    vector<JClass*>* getClasses(){
        return classes;
    }
};

void registerClasses(){
    JClassLoader::getBootClassLoader()->addClasses(JBootClassBuilder::getBootClassBuilder());
    JClassLoader::getBootClassLoader()->addClasses(new JSampleClassBuilder());
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
    QtDataOutputStream* qos=new QtDataOutputStream(qs);
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

int main(int argc, char *argv[])
{
    //TODO should be done by default ...
    registerClasses();

    testThrowable();

    //testMap();
    JSampleObject* sample=testReadSampleObject();
    testWriteSampleObject(sample);

    JClass* toto = JClass::getClazz();
    JObject object;
    cout<<object.toString();
    string str;
    cin>>str;
    cout<<object.getClass()->getSerialVersionUID();
    cin>>str;
    JDouble* jd=new JDouble(45);
    cout<<jd->toString();
    cin>>str;
    cout<<jd->getClass()->getSerialVersionUID();
    cout<<"clazz=="<<JClass::getClazz()->getName();
    cout<<"jdouble class=="<<jd->getClass()->getName();
    cout<<"jdouble class.class=="<<jd->getClass()->getClass()->getName();
    cin>>str;
    return 0;
}

