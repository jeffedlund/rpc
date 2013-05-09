#include "JPrimitiveBooleanTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveBooleanTest::JPrimitiveBooleanTest():JTest(){
            w=NULL;
            r=NULL;
        }

        JString JPrimitiveBooleanTest::getFileName(){
            return "PrimitiveBoolean.ser";
        }

        JObject* JPrimitiveBooleanTest::testReflect(){
            JPrimitiveBoolean* s=new JPrimitiveBoolean(true);
            assert (s->getClass()->getName()=="boolean");
            return s;
        }

        JPrimitiveBooleanTest::~JPrimitiveBooleanTest(){
        }
    }
}


