#include "JTest.h"
#include "JSampleObject.h"

namespace jcpp{
    void JTest::testWrite(JObject* object){
        try{
            write ww=getWrite();
            if (ww!=NULL){
                QString name=QString::fromStdString(getFileName());
                QFile* file=new QFile(name);
                file->open(QIODevice::WriteOnly);
                QDataStream* qs=new QDataStream(file);
                QtDataOutputStream* qos=new QtDataOutputStream(qs,file);
                JObjectOutputStream* oos=new JObjectOutputStream(qos);
                ww(oos,object);
                file->close();
            }
        }catch(JThrowable* th){
            th->printStackTrace(&cout);
            throw th;
        }
    }

    JObject* JTest::testRead(){
        try{
            read rr=getRead();
            if (rr!=NULL){
                QString name=QString::fromStdString(getFileName());
                QFile* file=new QFile(name);
                file->open(QIODevice::ReadOnly);
                QDataStream* qs=new QDataStream(file);
                QtDataInputStream* qis=new QtDataInputStream(qs);
                JObjectInputStream* ois=new JObjectInputStream(qis);
                cout<<"bootloader=="<<JClassLoader::getBootClassLoader()->toString()<<"\r\n";
                cout<<"sampleobject classloader=="<<JSampleObject::getClazz()->getClassLoader()->toString()<<"\r\n";
                ois->setInputClassLoader(JSampleObject::getClazz()->getClassLoader());
                JObject* read2=rr(ois);
                file->close();
                return read2;
            }
        }catch(JThrowable* th){
            th->printStackTrace(&cout);
            throw th;
        }
        return NULL;
    }

    void JTest::test(){
        JObject* object=testReflect();
        testWrite(object);
        JObject* read=testRead();
        if (getRead()!=NULL && getWrite()!=NULL){
            cout<<"reflect==";
            if(object!=NULL){
                cout<<object;
            }
            cout<<"\r\n";
            cout<<"read==";
            if (read!=NULL){
                cout<<read;
            }
            cout<<"\r\n";
            cout.flush();
            if (applyEqual()){
                assert ((*read)==(*object));
            }
        }
    }

    JTest::~JTest(){
    }
}
