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

using namespace std;


void testSampleObject(){
    QString name("E:\\project\\rpc\\io\\src\\main\\java\\output.b");
    QFile* file=new QFile(name);
    QDataStream* qs=new QDataStream(file);
    QtDataInputStream* qis=new QtDataInputStream(qs);
    JObjectInputStream ois=new JObjectInputStream(qis);
    JSampleObject* sample=(JSampleObject*)ois.readObject();
    cout<<sample->toString();
}

int main(int argc, char *argv[])
{
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

