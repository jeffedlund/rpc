#include "JClassNotFoundExceptionTest.h"

namespace jcpp{
    namespace lang{
        JClassNotFoundExceptionTest::JClassNotFoundExceptionTest():JExceptionTest(){
        }

        string JClassNotFoundExceptionTest::getFileName(){
            return "ClassNotFoundexception.ser";
        }

        JThrowable* JClassNotFoundExceptionTest::createFirstCause(){
            return new JClassNotFoundException();
        }

        JThrowable* JClassNotFoundExceptionTest::createSecondCause(){
            return new JClassNotFoundException();
        }

        string JClassNotFoundExceptionTest::getThrowableClassName(){
            return "java.lang.ClassNotFoundException";
        }
    }
}

