#include "JLongTest.h"

namespace jcpp{
    namespace lang{
        JLongTest::JLongTest():JTest(){
        }

        JString JLongTest::getFileName(){
            return "Long.ser";
        }

        JObject* JLongTest::testReflect(){
            JLong* s=new JLong(123456);
            assert (s->getClass()->getName()=="java.lang.Long");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveLong*)fvalue->get(s))->get()==123456);
            return s;
        }

        JLongTest::~JLongTest(){
        }
    }
}







