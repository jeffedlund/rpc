#include "JTest.h"

void JTest::testWrite(JObject* object){
    try{
        QString name=QString::fromStdString(getFileName());
        QFile* file=new QFile(name);
        file->open(QIODevice::WriteOnly);
        QDataStream* qs=new QDataStream(file);
        QtDataOutputStream* qos=new QtDataOutputStream(qs);
        JObjectOutputStream* oos=new JObjectOutputStream(qos);
        oos->writeObject(object);
        file->close();
    }catch(JThrowable* th){
        th->printStackTrace(&cout);
        throw th;
    }
}

JObject* JTest::testRead(){
    QString name=QString::fromStdString(getFileName());
    QFile* file=new QFile(name);
    file->open(QIODevice::ReadOnly);
    QDataStream* qs=new QDataStream(file);
    QtDataInputStream* qis=new QtDataInputStream(qs);
    JObjectInputStream* ois=new JObjectInputStream(qis);
    JObject* read=ois->readObject();
    file->close();
    return read;
}

void JTest::test(){
    JObject* object=testReflect();
    testWrite(object);
    JObject* read=testRead();
    assert ((*read)==(*object));
}
