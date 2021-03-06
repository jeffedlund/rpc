#ifndef JLONGTEST_H
#define JLONGTEST_H

#include "JLong.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JLongTest : public JTest{
        public:
            JLongTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JLongTest();
        };
    }
}

#endif // JLONGTEST_H
