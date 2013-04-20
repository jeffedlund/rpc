#ifndef JSTRINGBUILDERTEST_H
#define JSTRINGBUILDERTEST_H


#include "JStringBuilder.h"
#include "JTest.h"

namespace jcpp{
    namespace lang{
        class JStringBuilderTest : public JTest{
        public:
            JStringBuilderTest();

            string getFileName();

            JObject* testReflect();

            virtual ~JStringBuilderTest();
        };
    }
}
#endif // JSTRINGBUILDERTEST_H
