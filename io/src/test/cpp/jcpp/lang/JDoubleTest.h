#ifndef JDOUBLETEST_H
#define JDOUBLETEST_H

#include "JDouble.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JDoubleTest : public JTest{
        public:
            JDoubleTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JDOUBLETEST_H
