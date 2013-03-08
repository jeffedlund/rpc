#include "JNullPointerExceptionTest.h"

namespace jcpp{
    namespace lang{
        JNullPointerExceptionTest::JNullPointerExceptionTest():JRuntimeExceptionTest(){
        }

        string JNullPointerExceptionTest::getFileName(){
            return "NullPointerException.ser";
        }

        JThrowable* JNullPointerExceptionTest::createFirstCause(){
            return new JNullPointerException();
        }

        JThrowable* JNullPointerExceptionTest::createSecondCause(){
            return new JNullPointerException();
        }

        string JNullPointerExceptionTest::getThrowableClassName(){
            return "java.lang.NullPointerException";
        }

        JNullPointerExceptionTest::~JNullPointerExceptionTest(){
        }
    }
}
