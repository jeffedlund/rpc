#ifndef JTEST_H
#define JTEST_H

#include "assert.h"
#include "JIO.h"
#include "JLang.h"
#include "JUtil.h"
#include "JObject.h"
#include <QtGlobal>
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

        virtual string getFileName()=0;

        virtual JObject* testReflect()=0;

        void testWrite(JObject* object);

        JObject* testRead();

        void test();

        write getWrite(){
            return w;
        }

        read getRead(){
            return r;
        }
    };
}

#endif // JTEST_H
