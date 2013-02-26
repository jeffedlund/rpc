#ifndef JVIRTUALMACHINEERRORTEST_H
#define JVIRTUALMACHINEERRORTEST_H

#include "JErrorTest.h"
#include "JVirtualMachineError.h"

namespace jcpp{
    namespace lang{
        class JVirtualMachineErrorTest : public JErrorTest{
        public:
            JVirtualMachineErrorTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JVirtualMachineErrorTest();
        };
    }
}

#endif // JVIRTUALMACHINEERRORTEST_H
