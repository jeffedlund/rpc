#include "JTest.h"
#include "JSampleObject.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"

using namespace jcpp::io;

namespace jcpp{
    void JTest::testWrite(JObject* object){
        try{
            write ww=getWrite();
            if (ww!=NULL){
                JFileOutputStream* fos=new JFileOutputStream(getFileName());
                JObjectOutputStream* oos=new JObjectOutputStream(fos);
                ww(oos,object);
                fos->close();
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
                JFileInputStream* fis=new JFileInputStream(getFileName());
                JObjectInputStream* ois=new JObjectInputStream(fis);
                cout<<"bootloader=="<<JClassLoader::getBootClassLoader()->toString()<<"\r\n";
                cout<<"sampleobject classloader=="<<JSampleObject::getClazz()->getClassLoader()->toString()<<"\r\n";
                ois->setInputClassLoader(JSampleObject::getClazz()->getClassLoader());
                JObject* read2=rr(ois);
                fis->close();
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
