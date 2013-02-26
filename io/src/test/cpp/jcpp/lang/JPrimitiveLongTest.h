#ifndef JPRIMITIVELONGTEST_H
#define JPRIMITIVELONGTEST_H

#include "JPrimitiveLong.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveLongTest : public JTest{
        public:
            JPrimitiveLongTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JPrimitiveLongTest();
        };
    }
}

#endif // JPRIMITIVELONGTEST_H
