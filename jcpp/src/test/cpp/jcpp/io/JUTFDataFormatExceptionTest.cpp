#include "JUTFDataFormatExceptionTest.h"

namespace jcpp{
    namespace io{
        JUTFDataFormatExceptionTest::JUTFDataFormatExceptionTest():JIOExceptionTest(){
        }

        string JUTFDataFormatExceptionTest::getFileName(){
            return "UTFDataFormatException.ser";
        }

        JThrowable* JUTFDataFormatExceptionTest::createFirstCause(){
            return new JUTFDataFormatException();
        }

        JThrowable* JUTFDataFormatExceptionTest::createSecondCause(){
            return new JUTFDataFormatException();
        }

        string JUTFDataFormatExceptionTest::getThrowableClassName(){
            return "java.io.UTFDataFormatException";
        }

        JUTFDataFormatExceptionTest::~JUTFDataFormatExceptionTest(){
        }
    }
}
