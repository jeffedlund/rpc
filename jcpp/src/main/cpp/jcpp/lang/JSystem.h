#ifndef JSYSTEM_H
#define JSYSTEM_H

#include "JObject.h"
#include "Object.h"
#include "JCPP.h"
#include "JString.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JSystem : public JObject{//TODO implement other system methods
        protected:
        public:
            static JClass* getClazz();
            static jlong currentTimeMillis();
            static void arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length);
            static void arraycopy(jchar src[],jint srcPos, jchar dest[], jint destPos, jint length);
            static void arraycopy(JString src,jint srcPos, jchar dest[], jint destPos, jint length);
            static void arraycopy(JString* src,jint srcPos, jchar dest[], jint destPos, jint length);
            static void arraycopy(jchar src[],jint srcPos,vector<jchar>* dest,jint length);
            static void arraycopy(JString* src,jint srcPos,vector<jchar>* dest,jint length);
            static void arraycopy(JString src,jint srcPos,vector<jchar>* dest,jint length);
            virtual ~JSystem()=0;
        };
    }
}
#endif // JSYSTEM_H

