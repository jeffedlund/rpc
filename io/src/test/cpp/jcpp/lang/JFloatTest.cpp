#include "JFloatTest.h"

namespace jcpp{
    namespace lang{
        JFloatTest::JFloatTest():JTest(){
        }

        string JFloatTest::getFileName(){
            return "Float.ser";
        }

        JObject* JFloatTest::testReflect(){
            JFloat* s=new JFloat(123456);
            assert (s->getClass()->getName()=="java.lang.Float");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveFloat*)fvalue->get(s))->get()==123456);
            return s;
        }

        JFloatTest::~JFloatTest(){
        }
    }
}





