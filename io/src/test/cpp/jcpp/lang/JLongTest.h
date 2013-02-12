#ifndef JLONGTEST_H
#define JLONGTEST_H

#include "JLong.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JLongTest : public JTest{
        public:
            JLongTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JLONGTEST_H
