#ifndef JPRIMITIVEFLOAT_H
#define JPRIMITIVEFLOAT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveFloat : public JObject{

            protected:
                jfloat value;

            public:
                JPrimitiveFloat();
                JPrimitiveFloat(float value);
                bool operator==(JObject &other);
                JPrimitiveFloat operator+=(jfloat f);
                JPrimitiveFloat operator-=(jfloat f);
                JPrimitiveFloat operator*=(jfloat f);
                static JClass* getClazz();

                void set(jfloat value);

                jfloat get();

                string toString();

                virtual ~JPrimitiveFloat();
        };
    }
}

#endif // JPRIMITIVEFLOAT_H
