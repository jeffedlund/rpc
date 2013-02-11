#ifndef JUTFDATAFORMATEXCEPTIONTEST_H
#define JUTFDATAFORMATEXCEPTIONTEST_H

#include "JIOExceptionTest.h"
#include "JUTFDataFormatException.h"

namespace jcpp{
    namespace io{
        class JUTFDataFormatExceptionTest : public JIOExceptionTest{
        public:
            JUTFDataFormatExceptionTest();

            virtual string getFileName();

            virtual JThrowable* createFirstCause();

            virtual JThrowable* createSecondCause();

            virtual string getThrowableClassName();
        };
    }
}

#endif // JUTFDATAFORMATEXCEPTIONTEST_H
