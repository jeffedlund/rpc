#ifndef JBOOLEAN_H
#define JBOOLEAN_H

#include "JObject.h"
#include <vector>
#include <iostream>
#include "JPrimitiveBoolean.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JBoolean : public JObject{

            protected:
                JPrimitiveBoolean* value;

            public:
                JBoolean();
                JBoolean(bool value);
                JBoolean(JPrimitiveBoolean* value);
                bool operator==(JObject &other);

                static JClass* getClazz();

                void set(bool value);

                bool get();

                void setPrimitiveBoolean(JPrimitiveBoolean* value);

                JPrimitiveBoolean* getPrimitiveBoolean();

                string toString();

                ~JBoolean();
        };
    }
}
#endif // JBOOLEAN_H
