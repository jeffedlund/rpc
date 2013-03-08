#ifndef JVOID_H
#define JVOID_H

#include "JObject.h"
#include "JCPP.h"

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JVoid : public JObject{
            public:
                static JClass* getClazz();
                virtual ~JVoid()=0;
        };
    }
}
#endif // JVOID_H
