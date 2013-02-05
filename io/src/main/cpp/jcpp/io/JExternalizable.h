#ifndef JEXTERNALIZABLE_H
#define JEXTERNALIZABLE_H

#include "JObject.h"
#include "JClass.h"

//TODO implement correctly serializable + externalizable
class JExternalizable:JObject{
protected:
    JExternalizable();
public:

    static JClass* getClazz();

};

#endif // JEXTERNALIZABLE_H
