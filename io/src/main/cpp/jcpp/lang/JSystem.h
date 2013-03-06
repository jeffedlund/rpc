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
            //TODO void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length){
            virtual ~JSystem()=0;
        };
    }
}
#endif // JSYSTEM_H
