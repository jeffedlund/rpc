#include "JNoSuchFieldExceptionTest.h"

namespace jcpp{
    namespace lang{
        JNoSuchFieldExceptionTest::JNoSuchFieldExceptionTest():JExceptionTest(){
        }

        string JNoSuchFieldExceptionTest::getFileName(){
            return "NoSuchFieldexception.ser";
        }

        JThrowable* JNoSuchFieldExceptionTest::createFirstCause(){
            return new JNoSuchFieldException();
        }

        JThrowable* JNoSuchFieldExceptionTest::createSecondCause(){
            return new JNoSuchFieldException();
        }

        string JNoSuchFieldExceptionTest::getThrowableClassName(){
            return "java.lang.NoSuchFieldException";
        }
    }
}
