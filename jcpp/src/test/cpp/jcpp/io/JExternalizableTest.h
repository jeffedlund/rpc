#ifndef JEXTERNALIZABLETEST_H
#define JEXTERNALIZABLETEST_H

#include "JTest.h"
#include "JExternalizable.h"

namespace jcpp{
    namespace io{
        class JExternalizableTest : public JTest{
        public:
            JExternalizableTest();

            virtual string getFileName();

            virtual JObject* testReflect();

            virtual ~JExternalizableTest();
        };
    }
}

#endif // JEXTERNALIZABLETEST_H
