#include "JStringBufferTest.h"

namespace jcpp{
    namespace lang{
        JStringBufferTest::JStringBufferTest():JTest(){
        }

        string JStringBufferTest::getFileName(){
            return "StringBuffer.ser";
        }

        JObject* JStringBufferTest::testReflect(){
            JStringBuffer* s=new JStringBuffer();
            s->append(new JShort(1234));
            s->append((string)"toto");
            assert (s->getClass()->getName()=="java.lang.StringBuffer");
            assert (s->toString()=="1234toto");
            return s;
        }

        JStringBufferTest::~JStringBufferTest(){
        }
    }
}






