#ifndef JPRIMITIVESHORT_H
#define JPRIMITIVESHORT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveShort : public JObject, public JComparable{

            protected:
                jshort value;

            public:
                JPrimitiveShort();
                JPrimitiveShort(jshort value);
                JPrimitiveShort operator+=(jshort f);
                JPrimitiveShort operator-=(jshort f);
                JPrimitiveShort operator*=(jshort f);
                static JClass* getClazz();
                void set(jshort value);
                jshort get();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual string toString();
                virtual ~JPrimitiveShort();
        };
    }
}

#endif // JPRIMITIVESHORT_H
