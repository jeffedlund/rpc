#include "JByteTest.h"

namespace jcpp{
    namespace lang{
        JByteTest::JByteTest():JTest(){
        }

        string JByteTest::getFileName(){
            return "Byte.ser";
        }

        JObject* JByteTest::testReflect(){
            JByte* s=new JByte(10);
            assert (s->getClass()->getName()=="java.lang.Byte");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveByte*)fvalue->get(s))->get()==10);
            return s;
        }
    }
}


