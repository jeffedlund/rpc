#include "JInvalidClassExceptionTest.h"

namespace jcpp{
    namespace io{
        JInvalidClassExceptionTest::JInvalidClassExceptionTest():JObjectStreamExceptionTest(){
        }

        JString JInvalidClassExceptionTest::getFileName(){
            return "InvalidClassException.ser";
        }

        JThrowable* JInvalidClassExceptionTest::createFirstCause(){
            return new JInvalidClassException();
        }

        JThrowable* JInvalidClassExceptionTest::createSecondCause(){
            return new JInvalidClassException();
        }

        JString JInvalidClassExceptionTest::getThrowableClassName(){
            return "java.io.InvalidClassException";
        }

        JInvalidClassExceptionTest::~JInvalidClassExceptionTest(){
        }
    }
}






