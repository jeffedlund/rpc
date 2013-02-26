#include "JInternalErrorTest.h"

namespace jcpp{
    namespace lang{
        JInternalErrorTest::JInternalErrorTest():JVirtualMachineErrorTest(){
        }

        string JInternalErrorTest::getFileName(){
            return "InternalError.ser";
        }

        JThrowable* JInternalErrorTest::createFirstCause(){
            return new JInternalError();
        }

        JThrowable* JInternalErrorTest::createSecondCause(){
            return new JInternalError();
        }

        string JInternalErrorTest::getThrowableClassName(){
            return "java.lang.InternalError";
        }

        JInternalErrorTest::~JInternalErrorTest(){
        }
    }
}


