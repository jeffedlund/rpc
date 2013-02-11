#include "JIndexOutOfBoundsExceptionTest.h"

namespace jcpp{
    namespace lang{
        JIndexOutOfBoundsExceptionTest::JIndexOutOfBoundsExceptionTest():JRuntimeExceptionTest(){
        }

        string JIndexOutOfBoundsExceptionTest::getFileName(){
            return "IndexOutOfBoundsException.ser";
        }

        JThrowable* JIndexOutOfBoundsExceptionTest::createFirstCause(){
            return new JIndexOutOfBoundsException();
        }

        JThrowable* JIndexOutOfBoundsExceptionTest::createSecondCause(){
            return new JIndexOutOfBoundsException();
        }

        string JIndexOutOfBoundsExceptionTest::getThrowableClassName(){
            return "java.lang.IndexOutOfBoundsException";
        }
    }
}


