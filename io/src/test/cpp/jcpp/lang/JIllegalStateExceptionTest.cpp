#include "JIllegalStateExceptionTest.h"

namespace jcpp{
    namespace lang{
        JIllegalStateExceptionTest::JIllegalStateExceptionTest():JRuntimeExceptionTest(){
        }

        string JIllegalStateExceptionTest::getFileName(){
            return "IllegalStateException.ser";
        }

        JThrowable* JIllegalStateExceptionTest::createFirstCause(){
            return new JIllegalStateException();
        }

        JThrowable* JIllegalStateExceptionTest::createSecondCause(){
            return new JIllegalStateException();
        }

        string JIllegalStateExceptionTest::getThrowableClassName(){
            return "java.lang.IllegalStateException";
        }
    }
}

