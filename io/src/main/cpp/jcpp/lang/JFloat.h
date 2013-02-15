#ifndef JFLOAT_H
#define JFLOAT_H

#include "JObject.h"
#include "JNumber.h"
#include <vector>
#include <iostream>
#include "JPrimitiveFloat.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JFloat : public JNumber{

            protected:
                JPrimitiveFloat* value;

            public:
                JFloat();
                JFloat(float value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(float value);

                float get();

                void setPrimitiveFloat(JPrimitiveFloat* value);

                JPrimitiveFloat* getPrimitiveFloat();

                string toString();

                ~JFloat();
        };
    }
}

#endif // JFLOAT_H
