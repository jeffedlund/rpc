#include "JNotSerializableExceptionTest.h"

namespace jcpp{
    namespace io{
        JNotSerializableExceptionTest::JNotSerializableExceptionTest():JObjectStreamExceptionTest(){
        }

        JString JNotSerializableExceptionTest::getFileName(){
            return "NotSerializableException.ser";
        }

        JThrowable* JNotSerializableExceptionTest::createFirstCause(){
            return new JNotSerializableException();
        }

        JThrowable* JNotSerializableExceptionTest::createSecondCause(){
            return new JNotSerializableException();
        }

        JString JNotSerializableExceptionTest::getThrowableClassName(){
            return "java.io.NotSerializableException";
        }

        JNotSerializableExceptionTest::~JNotSerializableExceptionTest(){
        }
    }
}







