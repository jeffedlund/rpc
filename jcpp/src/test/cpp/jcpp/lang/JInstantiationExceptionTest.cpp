#include "JInstantiationExceptionTest.h"

namespace jcpp{
    namespace lang{
        JInstantiationExceptionTest::JInstantiationExceptionTest():JRuntimeExceptionTest(){
        }

        JString JInstantiationExceptionTest::getFileName(){
            return "InstantiationException.ser";
        }

        JThrowable* JInstantiationExceptionTest::createFirstCause(){
            return new JInstantiationException();
        }

        JThrowable* JInstantiationExceptionTest::createSecondCause(){
            return new JInstantiationException();
        }

        JString JInstantiationExceptionTest::getThrowableClassName(){
            return "java.lang.InstantiationException";
        }

        JInstantiationExceptionTest::~JInstantiationExceptionTest(){
        }
    }
}



