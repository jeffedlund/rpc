#ifndef JOPTIONALDATAEXCEPTIONTEST_H
#define JOPTIONALDATAEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JOptionalDataException.h"

namespace jcpp{
    namespace io{
        class JOptionalDataExceptionTest : public JObjectStreamExceptionTest{
        public:
            JOptionalDataExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JOptionalDataExceptionTest();
        };
    }
}

#endif // JOPTIONALDATAEXCEPTIONTEST_H
