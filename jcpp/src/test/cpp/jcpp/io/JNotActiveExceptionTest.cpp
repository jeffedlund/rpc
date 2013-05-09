#include "JNotActiveExceptionTest.h"

namespace jcpp{
    namespace io{
        JNotActiveExceptionTest::JNotActiveExceptionTest():JObjectStreamExceptionTest(){
        }

        JString JNotActiveExceptionTest::getFileName(){
            return "NotActiveException.ser";
        }

        JThrowable* JNotActiveExceptionTest::createFirstCause(){
            return new JNotActiveException();
        }

        JThrowable* JNotActiveExceptionTest::createSecondCause(){
            return new JNotActiveException();
        }

        JString JNotActiveExceptionTest::getThrowableClassName(){
            return "java.io.NotActiveException";
        }

        JNotActiveExceptionTest::~JNotActiveExceptionTest(){
        }
    }
}







