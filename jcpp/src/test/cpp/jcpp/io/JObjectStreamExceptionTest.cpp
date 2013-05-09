#include "JObjectStreamExceptionTest.h"

namespace jcpp{
    namespace io{
        JObjectStreamExceptionTest::JObjectStreamExceptionTest():JIOExceptionTest(){
        }

        JString JObjectStreamExceptionTest::getFileName(){
            return "objectstreamException.ser";
        }

        JThrowable* JObjectStreamExceptionTest::createFirstCause(){
            return new JObjectStreamException();
        }

        JThrowable* JObjectStreamExceptionTest::createSecondCause(){
            return new JObjectStreamException();
        }

        JString JObjectStreamExceptionTest::getThrowableClassName(){
            return "java.io.ObjectStreamException";
        }

        JObjectStreamExceptionTest::~JObjectStreamExceptionTest(){
        }
    }
}





