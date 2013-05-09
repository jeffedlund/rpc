#include "JEnumTest.h"
#include "JEnumSample.h"

namespace jcpp{
    namespace lang{
        JEnumTest::JEnumTest():JTest(){
        }

        JString JEnumTest::getFileName(){
            return "Enum.ser";
        }

        JObject* JEnumTest::testReflect(){
            JPrimitiveArray* s=new JPrimitiveArray(JEnumSample::getClazz(),5);
            s->set(0,JEnumSample::E1);
            s->set(1,JEnumSample::E2);
            s->set(2,JEnumSample::E3);
            s->set(3,JEnumSample::E4);
            s->set(4,JEnumSample::E5);
            assert(JEnumSample::getClazz()->valueOf("E1")==JEnumSample::E1);
            assert(JEnumSample::getClazz()->valueOf("E2")==JEnumSample::E2);
            assert(JEnumSample::getClazz()->valueOf("E3")==JEnumSample::E3);
            assert(JEnumSample::getClazz()->valueOf("E4")==JEnumSample::E4);
            assert(JEnumSample::getClazz()->valueOf("E5")==JEnumSample::E5);
            return s;
        }

        JEnumTest::~JEnumTest(){
        }
    }
}





