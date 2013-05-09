#include "JClassCastExceptionTest.h"

namespace jcpp{
    namespace lang{
        JClassCastExceptionTest::JClassCastExceptionTest():JRuntimeExceptionTest(){
        }

        JString JClassCastExceptionTest::getFileName(){
            return "ClassCastException.ser";
        }

        JThrowable* JClassCastExceptionTest::createFirstCause(){
            return new JClassCastException();
        }

        JThrowable* JClassCastExceptionTest::createSecondCause(){
            return new JClassCastException();
        }

        JString JClassCastExceptionTest::getThrowableClassName(){
            return "java.lang.ClassCastException";
        }

        JClassCastExceptionTest::~JClassCastExceptionTest(){
        }
    }
}
