#ifndef JTEST_H
#define JTEST_H

#include "assert.h"
#include "JIO.h"
#include "JLANG.h"
#include "JUTIL.h"
#include "JObject.h"
#include <QFile>
#include <QString>
#include <QDataStream>

namespace jcpp{
    class JTest{
    public :
        typedef void (*write)(JObjectOutputStream* out,JObject* o);
        typedef JObject* (*read)(JObjectInputStream* in);
        write w;
        read r;

        static void defaultWrite(JObjectOutputStream* out,JObject* o){
            out->writeObject(o);
        }

        static JObject* defaultRead(JObjectInputStream* in){
            return in->readObject();
        }

        JTest(){
            w=defaultWrite;
            r=defaultRead;
        }

        virtual string getFileName(){
            return "";
        }

        virtual JObject* testReflect(){
            return NULL;
        }

        virtual bool applyEqual(){
            return true;
        }

        void testWrite(JObject* object);

        JObject* testRead();

        virtual void test();

        write getWrite(){
            return w;
        }

        read getRead(){
            return r;
        }

        virtual ~JTest();
    };
}

#endif // JTEST_H
