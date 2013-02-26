#ifndef JPRIMITIVEFLOAT_H
#define JPRIMITIVEFLOAT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveFloat : public JObject{

            protected:
                jfloat value;

            public:
                JPrimitiveFloat();
                JPrimitiveFloat(float value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jfloat value);

                jfloat get();

                string toString();

                virtual ~JPrimitiveFloat();
        };
    }
}

#endif // JPRIMITIVEFLOAT_H
