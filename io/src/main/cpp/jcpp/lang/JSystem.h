#ifndef JSYSTEM_H
#define JSYSTEM_H

#include "JObject.h"
#include "Object.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JSystem : public JObject{//TODO implement other system methods
        protected:
        public:
            static JClass* getClazz();
            static jlong currentTimeMillis();
            virtual ~JSystem()=0;
        };
    }
}
#endif // JSYSTEM_H
