#ifndef JACCESSIBLEOBJECT_H
#define JACCESSIBLEOBJECT_H

#include "JObject.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JAccessibleObject: public JObject{
            protected:
                JAccessibleObject(JClass* clazz);

            public:

                static JClass* getClazz();
            };
        }
    }
}

#endif // JACCESSIBLEOBJECT_H
