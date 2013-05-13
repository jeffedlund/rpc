#ifndef JSHORT_H
#define JSHORT_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveShort.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JShort : public JNumber, public JComparable{
            protected:
                JPrimitiveShort* value;
                void setPrimitiveShort(JPrimitiveShort* value);
                JPrimitiveShort* getPrimitiveShort();
                friend class JShortClass;

            public:
                JShort();
                JShort(jshort value);
                static JClass* getClazz();
                static jshort MIN_VALUE;
                static jshort MAX_VALUE;
                static jint SIZE;
                static jint BYTES;
                static JClass* TYPE;
                static jint hashCode(jshort);
                static jint compare(jshort x,jshort y);
                JShort& operator+=(jshort f);
                JShort& operator-=(jshort f);
                JShort& operator*=(jshort f);
                void set(jshort value);
                jshort get();
                virtual jbyte byteValue();
                virtual jshort shortValue();
                virtual jint intValue();
                virtual jlong longValue();
                virtual jfloat floatValue();
                virtual jdouble doubleValue();
                virtual jint compareTo(JObject* o);
                virtual jbool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JShort();
        };
    }
}

#endif // JSHORT_H

