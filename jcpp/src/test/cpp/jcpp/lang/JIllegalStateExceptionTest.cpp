#include "JIllegalStateExceptionTest.h"

namespace jcpp{
    namespace lang{
        JIllegalStateExceptionTest::JIllegalStateExceptionTest():JRuntimeExceptionTest(){
        }

        JString JIllegalStateExceptionTest::getFileName(){
            return "IllegalStateException.ser";
        }

        JThrowable* JIllegalStateExceptionTest::createFirstCause(){
            return new JIllegalStateException();
        }

        JThrowable* JIllegalStateExceptionTest::createSecondCause(){
            return new JIllegalStateException();
        }

        JString JIllegalStateExceptionTest::getThrowableClassName(){
            return "java.lang.IllegalStateException";
        }

        JIllegalStateExceptionTest::~JIllegalStateExceptionTest(){
        }
    }
}

