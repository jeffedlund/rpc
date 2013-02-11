#ifndef JPRIMITIVEBOOLEAN_H
#define JPRIMITIVEBOOLEAN_H

#include "Object.h"
#include "JObject.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JPrimitiveBoolean : public JObject{

            protected:
                jbool value;

            public:
                JPrimitiveBoolean();
                JPrimitiveBoolean(jbool value);

                static JClass* getClazz();

                void set(jbool value);

                bool get();

                string toString();

                ~JPrimitiveBoolean();
        };
    }
}
#endif // JPRIMITIVEBOOLEAN_H
