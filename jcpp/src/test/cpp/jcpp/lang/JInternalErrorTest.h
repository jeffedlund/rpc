#ifndef JINTERNALERRORTEST_H
#define JINTERNALERRORTEST_H

#include "JInternalError.h"
#include "JVirtualMachineErrorTest.h"

namespace jcpp{
    namespace lang{
        class JInternalErrorTest : public JVirtualMachineErrorTest{
        public:
            JInternalErrorTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JInternalErrorTest();
        };
    }
}

#endif // JINTERNALERRORTEST_H
