#ifndef JSHORTTEST_H
#define JSHORTTEST_H

#include "JShort.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JShortTest : public JTest{
        public:
            JShortTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JSHORTTEST_H
