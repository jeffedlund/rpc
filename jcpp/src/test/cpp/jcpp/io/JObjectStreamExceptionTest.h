#ifndef JOBJECTSTREAMEXCEPTIONTEST_H
#define JOBJECTSTREAMEXCEPTIONTEST_H

#include "JIOExceptionTest.h"
#include "JObjectStreamException.h"

namespace jcpp{
    namespace io{
        class JObjectStreamExceptionTest : public JIOExceptionTest{
        public:
            JObjectStreamExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JObjectStreamExceptionTest();
        };
    }
}

#endif // JOBJECTSTREAMEXCEPTIONTEST_H
