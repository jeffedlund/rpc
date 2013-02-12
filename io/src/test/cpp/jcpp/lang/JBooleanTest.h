#ifndef JBOOLEANTEST_H
#define JBOOLEANTEST_H

#include "JBoolean.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JBooleanTest : public JTest{
        public:
            JBooleanTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JBOOLEANTEST_H
