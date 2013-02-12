#include "JStringTest.h"

namespace jcpp{
    namespace lang{
        JStringTest::JStringTest():JTest(){
        }

        string JStringTest::getFileName(){
            return "String.ser";
        }

        JObject* JStringTest::testReflect(){
            JString* s=new JString("123456");
            assert (s->getClass()->getName()=="java.lang.String");
            return s;
        }
    }
}








