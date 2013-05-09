#include "JPrimitiveCharTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveCharTest::JPrimitiveCharTest():JTest(){
            w=NULL;
            r=NULL;
        }

        JString JPrimitiveCharTest::getFileName(){
            return "PrimitiveChar.ser";
        }

        JObject* JPrimitiveCharTest::testReflect(){
            JPrimitiveChar* s=new JPrimitiveChar();
            assert (s->getClass()->getName()=="char");
            return s;
        }

        JPrimitiveCharTest::~JPrimitiveCharTest(){
        }
    }
}




