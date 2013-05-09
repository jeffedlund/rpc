#ifndef JSERIALIZABLETEST_H
#define JSERIALIZABLETEST_H

#include "JTest.h"

namespace jcpp{
    namespace io{
        class JSerializableTest : public JTest{
        public:
            JSerializableTest();

            virtual JString getFileName();

            virtual JObject* testReflect();

            virtual ~JSerializableTest();
        };
    }
}

#endif // JSERIALIZABLETEST_H
