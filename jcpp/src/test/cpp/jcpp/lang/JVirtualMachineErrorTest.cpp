#include "JVirtualMachineErrorTest.h"

namespace jcpp{
    namespace lang{
        JVirtualMachineErrorTest::JVirtualMachineErrorTest():JErrorTest(){
        }

        JString JVirtualMachineErrorTest::getFileName(){
            return "VirtualMachineError.ser";
        }

        JThrowable* JVirtualMachineErrorTest::createFirstCause(){
            return new JVirtualMachineError();
        }

        JThrowable* JVirtualMachineErrorTest::createSecondCause(){
            return new JVirtualMachineError();
        }

        JString JVirtualMachineErrorTest::getThrowableClassName(){
            return "java.lang.VirtualMachineError";
        }

        JVirtualMachineErrorTest::~JVirtualMachineErrorTest(){
        }
    }
}

