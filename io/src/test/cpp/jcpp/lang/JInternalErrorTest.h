#ifndef JINTERNALERRORTEST_H
#define JINTERNALERRORTEST_H

#include "JInternalError.h"
#include "JVirtualMachineErrorTest.h"

namespace jcpp{
    namespace lang{
        class JInternalErrorTest : public JVirtualMachineErrorTest{
        public:
            JInternalErrorTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JINTERNALERRORTEST_H
