#ifndef JEXTERNALIZABLE_H
#define JEXTERNALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JObjectOutputStream.h"

//TODO implement correctly serializable + externalizable
class JExternalizable:JObject{
protected:
    JExternalizable();
public:

    static JClass* getClazz();

    virtual void writeExternal(JObjectOutputStream* out)=0;//TODO implement readExternal

};

#endif // JEXTERNALIZABLE_H
