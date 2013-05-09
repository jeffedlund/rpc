#include "JIllegalArgumentExceptionTest.h"

namespace jcpp{
    namespace lang{
        JIllegalArgumentExceptionTest::JIllegalArgumentExceptionTest():JRuntimeExceptionTest(){
        }

        JString JIllegalArgumentExceptionTest::getFileName(){
            return "IllegalArgumentException.ser";
        }

        JThrowable* JIllegalArgumentExceptionTest::createFirstCause(){
            return new JIllegalArgumentException();
        }

        JThrowable* JIllegalArgumentExceptionTest::createSecondCause(){
            return new JIllegalArgumentException();
        }

        JString JIllegalArgumentExceptionTest::getThrowableClassName(){
            return "java.lang.IllegalArgumentException";
        }

        JIllegalArgumentExceptionTest::~JIllegalArgumentExceptionTest(){
        }
    }
}
