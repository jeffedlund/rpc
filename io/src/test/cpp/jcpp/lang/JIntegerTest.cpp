#include "JIntegerTest.h"

namespace jcpp{
    namespace lang{
        JIntegerTest::JIntegerTest():JTest(){
        }

        string JIntegerTest::getFileName(){
            return "Integer.ser";
        }

        JObject* JIntegerTest::testReflect(){
            JInteger* s=new JInteger(123456);
            assert (s->getClass()->getName()=="java.lang.Integer");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveInt*)fvalue->get(s))->get()==123456);
            return s;
        }
    }
}






