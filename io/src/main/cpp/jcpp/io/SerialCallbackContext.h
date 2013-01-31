#ifndef SERIALCALLBACKCONTEXT_H
#define SERIALCALLBACKCONTEXT_H

class JObjectStreamClass;
#include "JObject.h"

// Equivalent to SerialCallBackContext in Java
class SerialCallbackContext {
    JObject* curObj;
    JObjectStreamClass* curDesc;
    bool upcall;
public:
    SerialCallbackContext();

    bool setUpcall(bool v);

    bool isUpcall();

    JObject* getObj();

    JObjectStreamClass* getDesc();

    void setContext(JObject* obj, JObjectStreamClass* desc);

    void clear();
};

#endif // SERIALCALLBACKCONTEXT_H
