#include "JObjectStreamExceptionTest.h"

namespace jcpp{
    namespace io{
        JObjectStreamExceptionTest::JObjectStreamExceptionTest():JIOExceptionTest(){
        }

        string JObjectStreamExceptionTest::getFileName(){
            return "objectstreamException.ser";
        }

        JThrowable* JObjectStreamExceptionTest::createFirstCause(){
            return new JObjectStreamException();
        }

        JThrowable* JObjectStreamExceptionTest::createSecondCause(){
            return new JObjectStreamException();
        }

        string JObjectStreamExceptionTest::getThrowableClassName(){
            return "java.io.ObjectStreamException";
        }
    }
}





