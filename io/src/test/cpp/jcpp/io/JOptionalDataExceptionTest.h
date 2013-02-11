#ifndef JOPTIONALDATAEXCEPTIONTEST_H
#define JOPTIONALDATAEXCEPTIONTEST_H

#include "JObjectStreamExceptionTest.h"
#include "JOptionalDataException.h"

namespace jcpp{
    namespace io{
        class JOptionalDataExceptionTest : public JObjectStreamExceptionTest{
        public:
            JOptionalDataExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JOPTIONALDATAEXCEPTIONTEST_H
