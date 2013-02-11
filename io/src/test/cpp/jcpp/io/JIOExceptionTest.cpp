#include "JIOExceptionTest.h"

namespace jcpp{
    namespace io{
        JIOExceptionTest::JIOExceptionTest():JExceptionTest(){
        }

        string JIOExceptionTest::getFileName(){
            return "IOException.ser";
        }

        JThrowable* JIOExceptionTest::createFirstCause(){
            return new JIOException();
        }

        JThrowable* JIOExceptionTest::createSecondCause(){
            return new JIOException();
        }

        string JIOExceptionTest::getThrowableClassName(){
            return "java.io.IOException";
        }
    }
}



