#ifndef JCHARTEST_H
#define JCHARTEST_H

#include "JChar.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JCharTest : public JTest{
        public:
            JCharTest();

            string getFileName();

            JObject* testReflect();
        };
    }
}

#endif // JCHARTEST_H
