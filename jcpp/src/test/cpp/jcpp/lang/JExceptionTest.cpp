#include "JExceptionTest.h"

namespace jcpp{
    namespace lang{
        JExceptionTest::JExceptionTest():JThrowableTest(){
        }

        JString JExceptionTest::getFileName(){
            return "exception.ser";
        }

        JThrowable* JExceptionTest::createFirstCause(){
            return new JException();
        }

        JThrowable* JExceptionTest::createSecondCause(){
            return new JException();
        }

        JString JExceptionTest::getThrowableClassName(){
            return "java.lang.Exception";
        }

        JExceptionTest::~JExceptionTest(){
        }
    }
}

