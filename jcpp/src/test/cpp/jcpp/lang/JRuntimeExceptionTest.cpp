#include "JRuntimeExceptionTest.h"

namespace jcpp{
    namespace lang{
        JRuntimeExceptionTest::JRuntimeExceptionTest():JExceptionTest(){
        }

        JString JRuntimeExceptionTest::getFileName(){
            return "runtimeexception.ser";
        }

        JThrowable* JRuntimeExceptionTest::createFirstCause(){
            return new JRuntimeException();
        }

        JThrowable* JRuntimeExceptionTest::createSecondCause(){
            return new JRuntimeException();
        }

        JString JRuntimeExceptionTest::getThrowableClassName(){
            return "java.lang.RuntimeException";
        }

        JRuntimeExceptionTest::~JRuntimeExceptionTest(){
        }
    }
}
