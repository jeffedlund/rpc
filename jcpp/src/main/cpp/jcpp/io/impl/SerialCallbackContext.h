#ifndef SERIALCALLBACKCONTEXT_H
#define SERIALCALLBACKCONTEXT_H

#include "JObject.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JObjectStreamClass;
        class SerialCallbackContext {
            JObject* curObj;
            JObjectStreamClass* curDesc;
            jbool upcall;

        public:
            SerialCallbackContext();
            jbool setUpcall(jbool v);
            jbool isUpcall();
            JObject* getObj();
            JObjectStreamClass* getDesc();
            void setContext(JObject* obj, JObjectStreamClass* desc);
            void clear();
        };
    }
}

#endif // SERIALCALLBACKCONTEXT_H
