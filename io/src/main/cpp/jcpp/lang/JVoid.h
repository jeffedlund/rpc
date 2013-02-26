#ifndef JVOID_H
#define JVOID_H

#include "JObject.h"

namespace jcpp{
    namespace lang{
        class JVoid : public JObject{
            public:
                static JClass* getClazz();
                virtual ~JVoid()=0;
        };
    }
}
#endif // JVOID_H
