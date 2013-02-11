#include "JNoSuchMethodExceptionTest.h"

namespace jcpp{
    namespace lang{
        JNoSuchMethodExceptionTest::JNoSuchMethodExceptionTest():JExceptionTest(){
        }

        string JNoSuchMethodExceptionTest::getFileName(){
            return "NoSuchMethodexception.ser";
        }

        JThrowable* JNoSuchMethodExceptionTest::createFirstCause(){
            return new JNoSuchMethodException();
        }

        JThrowable* JNoSuchMethodExceptionTest::createSecondCause(){
            return new JNoSuchMethodException();
        }

        string JNoSuchMethodExceptionTest::getThrowableClassName(){
            return "java.lang.NoSuchMethodException";
        }
    }
}
