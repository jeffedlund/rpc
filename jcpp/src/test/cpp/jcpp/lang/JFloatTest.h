#ifndef JFLOATTEST_H
#define JFLOATTEST_H

#include "JFloat.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JFloatTest : public JTest{
        public:
            JFloatTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JFloatTest();
        };
    }
}

#endif // JFLOATTEST_H
