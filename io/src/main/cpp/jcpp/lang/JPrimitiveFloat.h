#ifndef JPRIMITIVEFLOAT_H
#define JPRIMITIVEFLOAT_H

#include "JObject.h"
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveFloat : public JObject{

            protected:
                float value;

            public:
                JPrimitiveFloat();
                JPrimitiveFloat(float value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(float value);

                float get();

                string toString();

                ~JPrimitiveFloat();
        };
    }
}

#endif // JPRIMITIVEFLOAT_H
