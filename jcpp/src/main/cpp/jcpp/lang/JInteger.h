#ifndef JINTEGER_H
#define JINTEGER_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "Object.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JInteger : public JNumber, public JComparable{

            protected:
                JPrimitiveInt* value;
                void setPrimitiveInt(JPrimitiveInt* value);
                JPrimitiveInt* getPrimitiveInt();
                friend class JIntegerClass;

            public:
                JInteger();
                JInteger(jint value);
                static JClass* getClazz();
                static jint hashCode(jint i);
                static jint compare(jint x,jint y);
                static jint MIN_VALUE;
                static jint MAX_VALUE;
                static jint SIZE;
                static jint BYTES;
                static JClass* TYPE;
                JInteger operator+=(jint f);
                JInteger operator-=(jint f);
                JInteger operator*=(jint f);
                void set(jint value);
                jint get();
                virtual jbyte byteValue();
                virtual jshort shortValue();
                virtual jint intValue();
                virtual jlong longValue();
                virtual jfloat floatValue();
                virtual jdouble doubleValue();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                virtual JString toString();
                virtual ~JInteger();
        };
    }
}

#endif // JINTEGER_H
