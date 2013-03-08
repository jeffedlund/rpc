#ifndef JSHORT_H
#define JSHORT_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveShort.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JShort : public JNumber{
            protected:
                JPrimitiveShort* value;

            public:
                JShort();
                JShort(jshort value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jshort value);

                jshort get();

                void setPrimitiveShort(JPrimitiveShort* value);

                JPrimitiveShort* getPrimitiveShort();

                string toString();

                virtual ~JShort();
        };
    }
}

#endif // JSHORT_H

