#ifndef JFLOATTEST_H
#define JFLOATTEST_H

#include "JFloat.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JFloatTest : public JTest{
        public:
            JFloatTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JFLOATTEST_H
