#include "JPrimitiveDoubleTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveDoubleTest::JPrimitiveDoubleTest():JTest(){
            w=NULL;
            r=NULL;
        }

        string JPrimitiveDoubleTest::getFileName(){
            return "PrimitiveDouble.ser";
        }

        JObject* JPrimitiveDoubleTest::testReflect(){
            JPrimitiveDouble* s=new JPrimitiveDouble();
            assert (s->getClass()->getName()=="double");
            return s;
        }
    }
}





