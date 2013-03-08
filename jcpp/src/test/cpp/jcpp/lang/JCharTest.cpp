#include "JCharTest.h"

namespace jcpp{
    namespace lang{
        JCharTest::JCharTest():JTest(){
        }

        string JCharTest::getFileName(){
            return "Char.ser";
        }

        JObject* JCharTest::testReflect(){
            JChar* s=new JChar('d');
            assert (s->getClass()->getName()=="java.lang.Character");
            JField* fvalue=s->getClass()->getField("value");
            assert (((JPrimitiveChar*)fvalue->get(s))->get()=='d');
            return s;
        }

        JCharTest::~JCharTest(){
        }
    }
}



