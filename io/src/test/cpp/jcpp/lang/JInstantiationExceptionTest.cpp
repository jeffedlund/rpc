#include "JInstantiationExceptionTest.h"

namespace jcpp{
    namespace lang{
        JInstantiationExceptionTest::JInstantiationExceptionTest():JRuntimeExceptionTest(){
        }

        string JInstantiationExceptionTest::getFileName(){
            return "InstantiationException.ser";
        }

        JThrowable* JInstantiationExceptionTest::createFirstCause(){
            return new JInstantiationException();
        }

        JThrowable* JInstantiationExceptionTest::createSecondCause(){
            return new JInstantiationException();
        }

        string JInstantiationExceptionTest::getThrowableClassName(){
            return "java.lang.InstantiationException";
        }
    }
}



