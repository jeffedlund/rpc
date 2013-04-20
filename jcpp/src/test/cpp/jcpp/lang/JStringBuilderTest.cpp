#include "JStringBuilderTest.h"

namespace jcpp{
    namespace lang{
        JStringBuilderTest::JStringBuilderTest():JTest(){
        }

        string JStringBuilderTest::getFileName(){
            return "StringBuilder.ser";
        }

        JObject* JStringBuilderTest::testReflect(){
            JStringBuilder* s=new JStringBuilder();
            s->append(new JShort(1234));
            s->append((string)"toto");
            assert (s->getClass()->getName()=="java.lang.StringBuilder");
            assert (s->toString()=="1234toto");
            return s;
        }

        JStringBuilderTest::~JStringBuilderTest(){
        }
    }
}





