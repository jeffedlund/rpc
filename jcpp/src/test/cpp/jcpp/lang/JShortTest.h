#ifndef JSHORTTEST_H
#define JSHORTTEST_H

#include "JShort.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JShortTest : public JTest{
        public:
            JShortTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JShortTest();
        };
    }
}

#endif // JSHORTTEST_H
