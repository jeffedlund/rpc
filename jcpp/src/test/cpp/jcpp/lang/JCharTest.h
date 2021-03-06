#ifndef JCHARTEST_H
#define JCHARTEST_H

#include "JChar.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JCharTest : public JTest{
        public:
            JCharTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JCharTest();
        };
    }
}

#endif // JCHARTEST_H
