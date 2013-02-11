#include "JUnsupportedOperationExceptionTest.h"

namespace jcpp{
    namespace lang{
        JUnsupportedOperationExceptionTest::JUnsupportedOperationExceptionTest():JRuntimeExceptionTest(){
        }

        string JUnsupportedOperationExceptionTest::getFileName(){
            return "UnsupportedOperationException.ser";
        }

        JThrowable* JUnsupportedOperationExceptionTest::createFirstCause(){
            return new JUnsupportedOperationException();
        }

        JThrowable* JUnsupportedOperationExceptionTest::createSecondCause(){
            return new JUnsupportedOperationException();
        }

        string JUnsupportedOperationExceptionTest::getThrowableClassName(){
            return "java.lang.UnsupportedOperationException";
        }
    }
}
