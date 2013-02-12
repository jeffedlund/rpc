#include "JDoubleTest.h"

namespace jcpp{
    namespace lang{
        JDoubleTest::JDoubleTest():JTest(){
        }

        string JDoubleTest::getFileName(){
            return "Double.ser";
        }

        JObject* JDoubleTest::testReflect(){
            JDouble* s=new JDouble(123456);
            assert (s->getClass()->getName()=="java.lang.Double");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveDouble*)fvalue->get(s))->get()==123456);
            return s;
        }
    }
}




