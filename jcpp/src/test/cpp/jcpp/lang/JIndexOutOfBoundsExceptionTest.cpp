#include "JIndexOutOfBoundsExceptionTest.h"

namespace jcpp{
    namespace lang{
        JIndexOutOfBoundsExceptionTest::JIndexOutOfBoundsExceptionTest():JRuntimeExceptionTest(){
        }

        JString JIndexOutOfBoundsExceptionTest::getFileName(){
            return "IndexOutOfBoundsException.ser";
        }

        JThrowable* JIndexOutOfBoundsExceptionTest::createFirstCause(){
            return new JIndexOutOfBoundsException();
        }

        JThrowable* JIndexOutOfBoundsExceptionTest::createSecondCause(){
            return new JIndexOutOfBoundsException();
        }

        JString JIndexOutOfBoundsExceptionTest::getThrowableClassName(){
            return "java.lang.IndexOutOfBoundsException";
        }

        JIndexOutOfBoundsExceptionTest::~JIndexOutOfBoundsExceptionTest(){
        }
    }
}


