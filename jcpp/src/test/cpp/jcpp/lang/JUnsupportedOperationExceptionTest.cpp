#include "JUnsupportedOperationExceptionTest.h"

namespace jcpp{
    namespace lang{
        JUnsupportedOperationExceptionTest::JUnsupportedOperationExceptionTest():JRuntimeExceptionTest(){
        }

        JString JUnsupportedOperationExceptionTest::getFileName(){
            return "UnsupportedOperationException.ser";
        }

        JThrowable* JUnsupportedOperationExceptionTest::createFirstCause(){
            return new JUnsupportedOperationException();
        }

        JThrowable* JUnsupportedOperationExceptionTest::createSecondCause(){
            return new JUnsupportedOperationException();
        }

        JString JUnsupportedOperationExceptionTest::getThrowableClassName(){
            return "java.lang.UnsupportedOperationException";
        }

        JUnsupportedOperationExceptionTest::~JUnsupportedOperationExceptionTest(){
        }
    }
}
