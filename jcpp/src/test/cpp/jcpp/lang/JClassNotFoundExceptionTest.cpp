#include "JClassNotFoundExceptionTest.h"

namespace jcpp{
    namespace lang{
        JClassNotFoundExceptionTest::JClassNotFoundExceptionTest():JExceptionTest(){
        }

        JString JClassNotFoundExceptionTest::getFileName(){
            return "ClassNotFoundexception.ser";
        }

        JThrowable* JClassNotFoundExceptionTest::createFirstCause(){
            return new JClassNotFoundException();
        }

        JThrowable* JClassNotFoundExceptionTest::createSecondCause(){
            return new JClassNotFoundException();
        }

        JString JClassNotFoundExceptionTest::getThrowableClassName(){
            return "java.lang.ClassNotFoundException";
        }

        JClassNotFoundExceptionTest::~JClassNotFoundExceptionTest(){
        }
    }
}

