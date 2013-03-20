#ifndef JPRIMITIVEBOOLEAN_H
#define JPRIMITIVEBOOLEAN_H

#include "Object.h"
#include "JObject.h"
#include <vector>
#include <iostream>
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JPrimitiveBoolean : public JObject{

            protected:
                jbool value;

            public:
                JPrimitiveBoolean();
                JPrimitiveBoolean(jbool value);
                static JClass* getClazz();
                void set(jbool value);
                bool get();
                virtual bool equals(JObject* other);
                virtual string toString();

                virtual ~JPrimitiveBoolean();
        };
    }
}
#endif // JPRIMITIVEBOOLEAN_H
