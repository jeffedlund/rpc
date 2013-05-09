#ifndef JHASHSETTEST_H
#define JHASHSETTESt_H

#include "JHashSet.h"
#include "JTest.h"

namespace jcpp{
    namespace util{
        class JHashSetTest : public JTest{
        public:
            JHashSetTest();

            JString getFileName();

            JObject* testReflect();

            virtual ~JHashSetTest();
        };
    }
}
#endif // JHASHSETTEST_H
