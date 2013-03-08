#include "JErrorTest.h"

namespace jcpp{
    namespace lang{
        JErrorTest::JErrorTest():JThrowableTest(){
        }

        string JErrorTest::getFileName(){
            return "error.ser";
        }

        JThrowable* JErrorTest::createFirstCause(){
            return new JError();
        }

        JThrowable* JErrorTest::createSecondCause(){
            return new JError();
        }

        string JErrorTest::getThrowableClassName(){
            return "java.lang.Error";
        }

        JErrorTest::~JErrorTest(){
        }
    }
}