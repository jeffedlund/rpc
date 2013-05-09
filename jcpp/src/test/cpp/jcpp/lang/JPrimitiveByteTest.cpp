#include "JPrimitiveByteTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveByteTest::JPrimitiveByteTest():JTest(){
            w=NULL;
            r=NULL;
        }

        JString JPrimitiveByteTest::getFileName(){
            return "PrimitiveByte.ser";
        }

        JObject* JPrimitiveByteTest::testReflect(){
            JPrimitiveByte* s=new JPrimitiveByte();
            assert (s->getClass()->getName()=="byte");
            return s;
        }

        JPrimitiveByteTest::~JPrimitiveByteTest(){
        }
    }
}



