#ifndef JVIRTUALMACHINEERRORTEST_H
#define JVIRTUALMACHINEERRORTEST_H

#include "JErrorTest.h"
#include "JVirtualMachineError.h"

namespace jcpp{
    namespace lang{
        class JVirtualMachineErrorTest : public JErrorTest{
        public:
            JVirtualMachineErrorTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JVirtualMachineErrorTest();
        };
    }
}

#endif // JVIRTUALMACHINEERRORTEST_H
