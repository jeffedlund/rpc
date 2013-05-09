#ifndef JARRAYLISTTEST_H
#define JARRAYLISTTEST_H

#include "JArrayList.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JArrayListTest : public JTest{
        public:
            JArrayListTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JArrayListTest();
        };
    }
}

#endif // JARRAYLISTTEST_H
