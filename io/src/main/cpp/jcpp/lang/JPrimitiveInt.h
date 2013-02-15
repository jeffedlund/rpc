#ifndef JPRIMITIVEINT_H
#define JPRIMITIVEINT_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveInt : public JObject{

            protected:
                jint value;

            public:
                JPrimitiveInt();
                JPrimitiveInt(jint value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(jint value);

                jint get();

                string toString();

                ~JPrimitiveInt();
        };
    }
}

#endif // JPRIMITIVEINT_H
