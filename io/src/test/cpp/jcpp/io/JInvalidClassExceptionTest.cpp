#include "JInvalidClassExceptionTest.h"

namespace jcpp{
    namespace io{
        JInvalidClassExceptionTest::JInvalidClassExceptionTest():JObjectStreamExceptionTest(){
        }

        string JInvalidClassExceptionTest::getFileName(){
            return "InvalidClassException.ser";
        }

        JThrowable* JInvalidClassExceptionTest::createFirstCause(){
            return new JInvalidClassException();
        }

        JThrowable* JInvalidClassExceptionTest::createSecondCause(){
            return new JInvalidClassException();
        }

        string JInvalidClassExceptionTest::getThrowableClassName(){
            return "java.io.InvalidClassException";
        }
    }
}






