#include "JNotActiveExceptionTest.h"

namespace jcpp{
    namespace io{
        JNotActiveExceptionTest::JNotActiveExceptionTest():JObjectStreamExceptionTest(){
        }

        string JNotActiveExceptionTest::getFileName(){
            return "NotActiveException.ser";
        }

        JThrowable* JNotActiveExceptionTest::createFirstCause(){
            return new JNotActiveException();
        }

        JThrowable* JNotActiveExceptionTest::createSecondCause(){
            return new JNotActiveException();
        }

        string JNotActiveExceptionTest::getThrowableClassName(){
            return "java.io.NotActiveException";
        }
    }
}







