#include "JVirtualMachineErrorTest.h"

namespace jcpp{
    namespace lang{
        JVirtualMachineErrorTest::JVirtualMachineErrorTest():JErrorTest(){
        }

        string JVirtualMachineErrorTest::getFileName(){
            return "VirtualMachineError.ser";
        }

        JThrowable* JVirtualMachineErrorTest::createFirstCause(){
            return new JVirtualMachineError();
        }

        JThrowable* JVirtualMachineErrorTest::createSecondCause(){
            return new JVirtualMachineError();
        }

        string JVirtualMachineErrorTest::getThrowableClassName(){
            return "java.lang.VirtualMachineError";
        }

        JVirtualMachineErrorTest::~JVirtualMachineErrorTest(){
        }
    }
}

