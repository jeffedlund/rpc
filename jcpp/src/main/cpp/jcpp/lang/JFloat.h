#ifndef JFLOAT_H
#define JFLOAT_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveFloat.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JFloat : public JNumber{

            protected:
                JPrimitiveFloat* value;

            public:
                JFloat();
                JFloat(float value);
                static JClass* getClazz();
                static jfloat MIN_VALUE;
                static jfloat MAX_VALUE;
                static jint hashCode(jfloat f);
                JFloat operator+=(jfloat f);
                JFloat operator-=(jfloat f);
                JFloat operator*=(jfloat f);
                void set(float value);
                float get();
                void setPrimitiveFloat(JPrimitiveFloat* value);
                JPrimitiveFloat* getPrimitiveFloat();
                virtual bool equals(JObject* other);
                virtual jint hashCode();
                string toString();
                virtual ~JFloat();
        };
    }
}

#endif // JFLOAT_H
