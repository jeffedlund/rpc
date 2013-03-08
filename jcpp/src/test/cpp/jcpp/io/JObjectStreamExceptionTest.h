#ifndef JOBJECTSTREAMEXCEPTIONTEST_H
#define JOBJECTSTREAMEXCEPTIONTEST_H

#include "JIOExceptionTest.h"
#include "JObjectStreamException.h"

namespace jcpp{
    namespace io{
        class JObjectStreamExceptionTest : public JIOExceptionTest{
        public:
            JObjectStreamExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();

            virtual ~JObjectStreamExceptionTest();
        };
    }
}

#endif // JOBJECTSTREAMEXCEPTIONTEST_H
