#include "JPrimitiveLongTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveLongTest::JPrimitiveLongTest():JTest(){
            w=NULL;
            r=NULL;
        }

        JString JPrimitiveLongTest::getFileName(){
            return "PrimitiveLong.ser";
        }

        JObject* JPrimitiveLongTest::testReflect(){
            JPrimitiveLong* s=new JPrimitiveLong();
            assert (s->getClass()->getName()=="long");
            return s;
        }

        JPrimitiveLongTest::~JPrimitiveLongTest(){
        }
    }
}







