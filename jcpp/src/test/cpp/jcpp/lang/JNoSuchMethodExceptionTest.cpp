#include "JNoSuchMethodExceptionTest.h"

namespace jcpp{
    namespace lang{
        JNoSuchMethodExceptionTest::JNoSuchMethodExceptionTest():JExceptionTest(){
        }

        JString JNoSuchMethodExceptionTest::getFileName(){
            return "NoSuchMethodexception.ser";
        }

        JThrowable* JNoSuchMethodExceptionTest::createFirstCause(){
            return new JNoSuchMethodException();
        }

        JThrowable* JNoSuchMethodExceptionTest::createSecondCause(){
            return new JNoSuchMethodException();
        }

        JString JNoSuchMethodExceptionTest::getThrowableClassName(){
            return "java.lang.NoSuchMethodException";
        }

        JNoSuchMethodExceptionTest::~JNoSuchMethodExceptionTest(){
        }
    }
}
