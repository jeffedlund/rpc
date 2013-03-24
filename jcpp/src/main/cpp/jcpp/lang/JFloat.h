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

            public:
                JFloat();
                JFloat(float value);
                static JClass* getClazz();
                static jfloat MIN_VALUE;
                static jfloat MAX_VALUE;
                static jint hashCode(jfloat f);
                static jint compare(jfloat f1,jfloat f2);
                JFloat operator+=(jfloat f);
                JFloat operator-=(jfloat f);
                JFloat operator*=(jfloat f);
                void set(float value);
                float get();
                void setPrimitiveFloat(JPrimitiveFloat* value);
                JPrimitiveFloat* getPrimitiveFloat();
                virtual jint compareTo(JObject* o);
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                string toString();
                virtual ~JFloat();
        };
    }
}

#endif // JFLOAT_H
