#include "JPrimitiveIntTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveIntTest::JPrimitiveIntTest():JTest(){
            w=NULL;
            r=NULL;
        }

        JString JPrimitiveIntTest::getFileName(){
            return "PrimitiveInt.ser";
        }

        JObject* JPrimitiveIntTest::testReflect(){
            JPrimitiveInt* s=new JPrimitiveInt();
            assert (s->getClass()->getName()=="int");
            return s;
        }

        JPrimitiveIntTest::~JPrimitiveIntTest(){
        }
    }
}









