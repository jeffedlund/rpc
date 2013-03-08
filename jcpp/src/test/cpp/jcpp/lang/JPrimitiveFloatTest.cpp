#include "JPrimitiveFloatTest.h"

namespace jcpp{
    namespace lang{
        JPrimitiveFloatTest::JPrimitiveFloatTest():JTest(){
            w=NULL;
            r=NULL;
        }

        string JPrimitiveFloatTest::getFileName(){
            return "PrimitiveFloat.ser";
        }

        JObject* JPrimitiveFloatTest::testReflect(){
            JPrimitiveFloat* s=new JPrimitiveFloat();
            assert (s->getClass()->getName()=="float");
            return s;
        }

        JPrimitiveFloatTest::~JPrimitiveFloatTest(){
        }
    }
}






