#include "JOptionalDataExceptionTest.h"

namespace jcpp{
    namespace io{
        JOptionalDataExceptionTest::JOptionalDataExceptionTest():JObjectStreamExceptionTest(){
        }

        JString JOptionalDataExceptionTest::getFileName(){
            return "OptionalDataException.ser";
        }

        JThrowable* JOptionalDataExceptionTest::createFirstCause(){
            return new JOptionalDataException();
        }

        JThrowable* JOptionalDataExceptionTest::createSecondCause(){
            return new JOptionalDataException();
        }

        JString JOptionalDataExceptionTest::getThrowableClassName(){
            return "java.io.OptionalDataException";
        }

        JOptionalDataExceptionTest::~JOptionalDataExceptionTest(){
        }
    }
}







