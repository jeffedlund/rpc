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

void testSampleObject(){
    registerClasses();
    QString name("E:\\project\\rpc\\io\\src\\main\\java\\output.b");
    QFile* file=new QFile(name);
    file->open(QIODevice::ReadOnly);
    QDataStream* qs=new QDataStream(file);
    QtDataInputStream* qis=new QtDataInputStream(qs);
    JObjectInputStream* ois=new JObjectInputStream(qis);
    JSampleObject* sample=(JSampleObject*)ois->readObject();
    cout<<sample->toString();
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
    //testMap();
    testSampleObject();

    JClass* toto = JClass::getClazz();
    JObject object;
    cout<<object.toString();
    string str;
    cin>>str;
    cout<<object.getClass()->getSerialVersionUID();
    cin>>str;
    JDouble* jdouble=new JDouble(45);
    cout<<jdouble->toString();
    cin>>str;
    cout<<jdouble->getClass()->getSerialVersionUID();
    cout<<"clazz=="<<JClass::getClazz()->getName();
    cout<<"jdouble class=="<<jdouble->getClass()->getName();
    cout<<"jdouble class.class=="<<jdouble->getClass()->getClass()->getName();
    cin>>str;
    return 0;
}

