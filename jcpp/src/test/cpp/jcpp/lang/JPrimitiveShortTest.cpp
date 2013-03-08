#include "JPrimitiveShortTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveShortTest::JPrimitiveShortTest():JTest(){
            w=NULL;
            r=NULL;
        }

        string JPrimitiveShortTest::getFileName(){
            return "PrimitiveShort.ser";
        }

        JObject* JPrimitiveShortTest::testReflect(){
            JPrimitiveShort* s=new JPrimitiveShort();
            assert (s->getClass()->getName()=="short");
            return s;
        }

        JPrimitiveShortTest::~JPrimitiveShortTest(){
        }
    }
}








