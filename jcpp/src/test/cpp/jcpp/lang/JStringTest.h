#ifndef JSTRINGTEST_H
#define JSTRINGTEST_H

#include "JString.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JStringTest : public JTest{
        public:
            JStringTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JStringTest();
        };
    }
}

#endif // JSTRINGTEST_H
