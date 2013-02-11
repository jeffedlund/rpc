#include "JOptionalDataExceptionTest.h"

namespace jcpp{
    namespace io{
        JOptionalDataExceptionTest::JOptionalDataExceptionTest():JObjectStreamExceptionTest(){
        }

        string JOptionalDataExceptionTest::getFileName(){
            return "OptionalDataException.ser";
        }

        JThrowable* JOptionalDataExceptionTest::createFirstCause(){
            return new JOptionalDataException();
        }

        JThrowable* JOptionalDataExceptionTest::createSecondCause(){
            return new JOptionalDataException();
        }

        string JOptionalDataExceptionTest::getThrowableClassName(){
            return "java.io.OptionalDataException";
        }
    }
}







