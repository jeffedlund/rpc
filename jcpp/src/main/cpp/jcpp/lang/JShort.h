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
                virtual bool equals(JObject* other);
                JShort operator+=(jshort f);
                JShort operator-=(jshort f);
                JShort operator*=(jshort f);
                static JClass* getClazz();
                static jshort MIN_VALUE;
                static jshort MAX_VALUE;
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

