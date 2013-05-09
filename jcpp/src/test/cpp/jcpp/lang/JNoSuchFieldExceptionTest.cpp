#include "JNoSuchFieldExceptionTest.h"

namespace jcpp{
    namespace lang{
        JNoSuchFieldExceptionTest::JNoSuchFieldExceptionTest():JExceptionTest(){
        }

        JString JNoSuchFieldExceptionTest::getFileName(){
            return "NoSuchFieldexception.ser";
        }

        JThrowable* JNoSuchFieldExceptionTest::createFirstCause(){
            return new JNoSuchFieldException();
        }

        JThrowable* JNoSuchFieldExceptionTest::createSecondCause(){
            return new JNoSuchFieldException();
        }

        JString JNoSuchFieldExceptionTest::getThrowableClassName(){
            return "java.lang.NoSuchFieldException";
        }

        JNoSuchFieldExceptionTest::~JNoSuchFieldExceptionTest(){
        }
    }
}
