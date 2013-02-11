#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        JRuntimeExceptionTest::JRuntimeExceptionTest():JExceptionTest(){
        }

        string JRuntimeExceptionTest::getFileName(){
            return "runtimeexception.ser";
        }

        JThrowable* JRuntimeExceptionTest::createFirstCause(){
            return new JRuntimeException();
        }

        JThrowable* JRuntimeExceptionTest::createSecondCause(){
            return new JRuntimeException();
        }

        string JRuntimeExceptionTest::getThrowableClassName(){
            return "java.lang.RuntimeException";
        }
    }
}
