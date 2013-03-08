#include "JNotSerializableExceptionTest.h"

namespace jcpp{
    namespace io{
        JNotSerializableExceptionTest::JNotSerializableExceptionTest():JObjectStreamExceptionTest(){
        }

        string JNotSerializableExceptionTest::getFileName(){
            return "NotSerializableException.ser";
        }

        JThrowable* JNotSerializableExceptionTest::createFirstCause(){
            return new JNotSerializableException();
        }

        JThrowable* JNotSerializableExceptionTest::createSecondCause(){
            return new JNotSerializableException();
        }

        string JNotSerializableExceptionTest::getThrowableClassName(){
            return "java.io.NotSerializableException";
        }

        JNotSerializableExceptionTest::~JNotSerializableExceptionTest(){
        }
    }
}







