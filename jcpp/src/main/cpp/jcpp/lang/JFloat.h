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
                bool operator==(JObject &other);
                JFloat operator+=(jfloat f);
                JFloat operator-=(jfloat f);
                JFloat operator*=(jfloat f);
                static JClass* getClazz();
                void set(float value);
                float get();
                void setPrimitiveFloat(JPrimitiveFloat* value);
                JPrimitiveFloat* getPrimitiveFloat();
                string toString();
                virtual ~JFloat();
        };
    }
}

#endif // JFLOAT_H
