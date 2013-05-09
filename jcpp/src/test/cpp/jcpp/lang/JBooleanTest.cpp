#include "JBooleanTest.h"

namespace jcpp{
    namespace lang{
        JBooleanTest::JBooleanTest():JTest(){
        }

        JString JBooleanTest::getFileName(){
            return "Boolean.ser";
        }

        JObject* JBooleanTest::testReflect(){
            JBoolean* s=new JBoolean(true);
            assert (s->getClass()->getName()=="java.lang.Boolean");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveBoolean*)fvalue->get(s))->get()==true);
            return s;
        }

        JBooleanTest::~JBooleanTest(){
        }
    }
}

