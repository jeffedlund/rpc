#ifndef JDOUBLE_H
#define JDOUBLE_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveDouble.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JDouble : public JNumber, public JComparable{
            protected:
                JPrimitiveDouble* value;
                void setPrimitiveDouble(JPrimitiveDouble* value);
                JPrimitiveDouble* getPrimitiveDouble();
                friend class JDoubleClass;

            public:
                JDouble();
                JDouble(jdouble value);
                static JClass* getClazz();
                static jdouble MIN_VALUE;
                static jdouble MAX_VALUE;
                static jint SIZE;
                static jint BYTES;
                static JClass* TYPE;
                static jint hashCode(jdouble);
                static jint compare(jdouble d1,jdouble d2);
                JDouble operator+=(jdouble f);
                JDouble operator-=(jdouble f);
                JDouble operator*=(jdouble f);
                void set(jdouble value);
                jdouble get();
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
                virtual ~JDouble();
        };
    }
}

#endif // JDOUBLE_H
