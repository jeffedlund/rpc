#include "JClassCastExceptionTest.h"

namespace jcpp{
    namespace lang{
        JClassCastExceptionTest::JClassCastExceptionTest():JRuntimeExceptionTest(){
        }

        string JClassCastExceptionTest::getFileName(){
            return "ClassCastException.ser";
        }

        JThrowable* JClassCastExceptionTest::createFirstCause(){
            return new JClassCastException();
        }

        JThrowable* JClassCastExceptionTest::createSecondCause(){
            return new JClassCastException();
        }

        string JClassCastExceptionTest::getThrowableClassName(){
            return "java.lang.ClassCastException";
        }

        JClassCastExceptionTest::~JClassCastExceptionTest(){
        }
    }
}
