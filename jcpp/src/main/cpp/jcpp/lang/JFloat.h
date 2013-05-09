#ifndef JFLOAT_H
#define JFLOAT_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveFloat.h"
#include "JCPP.h"
#include "JComparable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JFloat : public JNumber, public JComparable{

            protected:
                JPrimitiveFloat* value;
                void setPrimitiveFloat(JPrimitiveFloat* value);
                JPrimitiveFloat* getPrimitiveFloat();
                friend class JFloatClass;

            public:
                JFloat();
                JFloat(jfloat value);
                static JClass* getClazz();
                static jfloat MIN_VALUE;
                static jfloat MAX_VALUE;
                static jint SIZE;
                static jint BYTES;
                static JClass* TYPE;
                static jint hashCode(jfloat f);
                static jint compare(jfloat f1,jfloat f2);
                JFloat operator+=(jfloat f);
                JFloat operator-=(jfloat f);
                JFloat operator*=(jfloat f);
                void set(float value);
                float get();
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
                virtual ~JFloat();
        };
    }
}

#endif // JFLOAT_H
