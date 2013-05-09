#include "JStreamCorruptedExceptionTest.h"

namespace jcpp{
    namespace io{
        JStreamCorruptedExceptionTest::JStreamCorruptedExceptionTest():JObjectStreamExceptionTest(){
        }

        JString JStreamCorruptedExceptionTest::getFileName(){
            return "StreamCorruptedException.ser";
        }

        JThrowable* JStreamCorruptedExceptionTest::createFirstCause(){
            return new JStreamCorruptedException();
        }

        JThrowable* JStreamCorruptedExceptionTest::createSecondCause(){
            return new JStreamCorruptedException();
        }

        JString JStreamCorruptedExceptionTest::getThrowableClassName(){
            return "java.io.StreamCorruptedException";
        }

        JStreamCorruptedExceptionTest::~JStreamCorruptedExceptionTest(){
        }
    }
}
