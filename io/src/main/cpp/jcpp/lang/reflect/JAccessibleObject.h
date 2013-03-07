#ifndef JACCESSIBLEOBJECT_H
#define JACCESSIBLEOBJECT_H

#include "JObject.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JAccessibleObject: public JObject{
            protected:
                JAccessibleObject(JClass* clazz);

            public:

                static JClass* getClazz();
                virtual ~JAccessibleObject();
            };
        }
    }
}

#endif // JACCESSIBLEOBJECT_H
