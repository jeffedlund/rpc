#ifndef JUTFDATAFORMATEXCEPTIONTEST_H
#define JUTFDATAFORMATEXCEPTIONTEST_H

#include "JIOExceptionTest.h"
#include "JUTFDataFormatException.h"

namespace jcpp{
    namespace io{
        class JUTFDataFormatExceptionTest : public JIOExceptionTest{
        public:
            JUTFDataFormatExceptionTest();

            virtual JString getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual JString getThrowableClassName();

            virtual ~JUTFDataFormatExceptionTest();
        };
    }
}

#endif // JUTFDATAFORMATEXCEPTIONTEST_H
