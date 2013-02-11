#include "JIllegalArgumentExceptionTest.h"

namespace jcpp{
    namespace lang{
        JIllegalArgumentExceptionTest::JIllegalArgumentExceptionTest():JRuntimeExceptionTest(){
        }

        string JIllegalArgumentExceptionTest::getFileName(){
            return "IllegalArgumentException.ser";
        }

        JThrowable* JIllegalArgumentExceptionTest::createFirstCause(){
            return new JIllegalArgumentException();
        }

        JThrowable* JIllegalArgumentExceptionTest::createSecondCause(){
            return new JIllegalArgumentException();
        }

        string JIllegalArgumentExceptionTest::getThrowableClassName(){
            return "java.lang.IllegalArgumentException";
        }
    }
}
