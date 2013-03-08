#include "JStreamCorruptedExceptionTest.h"

namespace jcpp{
    namespace io{
        JStreamCorruptedExceptionTest::JStreamCorruptedExceptionTest():JObjectStreamExceptionTest(){
        }

        string JStreamCorruptedExceptionTest::getFileName(){
            return "StreamCorruptedException.ser";
        }

        JThrowable* JStreamCorruptedExceptionTest::createFirstCause(){
            return new JStreamCorruptedException();
        }

        JThrowable* JStreamCorruptedExceptionTest::createSecondCause(){
            return new JStreamCorruptedException();
        }

        string JStreamCorruptedExceptionTest::getThrowableClassName(){
            return "java.io.StreamCorruptedException";
        }

        JStreamCorruptedExceptionTest::~JStreamCorruptedExceptionTest(){
        }
    }
}
