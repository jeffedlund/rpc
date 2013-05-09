#include "JIOExceptionTest.h"

namespace jcpp{
    namespace io{
        JIOExceptionTest::JIOExceptionTest():JExceptionTest(){
        }

        JString JIOExceptionTest::getFileName(){
            return "IOException.ser";
        }

        JThrowable* JIOExceptionTest::createFirstCause(){
            return new JIOException();
        }

        JThrowable* JIOExceptionTest::createSecondCause(){
            return new JIOException();
        }

        JString JIOExceptionTest::getThrowableClassName(){
            return "java.io.IOException";
        }

        JIOExceptionTest::~JIOExceptionTest(){
        }
    }
}



