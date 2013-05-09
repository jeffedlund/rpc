#ifndef JHASHTABLETEST_H
#define JHASHTABLETEST_H


#include "JHashtable.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JHashtableTest : public JTest{
        public:
            JHashtableTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JHashtableTest();
        };
    }
}
#endif // JHASHTABLETEST_H
