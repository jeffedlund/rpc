#include "JShortTest.h"

namespace jcpp{
    namespace lang{
        JShortTest::JShortTest():JTest(){
        }

        string JShortTest::getFileName(){
            return "short.ser";
        }

        JObject* JShortTest::testReflect(){
            JShort* s=new JShort(123);
            assert (s->getClass()->getName()=="java.lang.Short");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveShort*)fvalue->get(s))->get()==123);
            return s;
        }
    }
}
