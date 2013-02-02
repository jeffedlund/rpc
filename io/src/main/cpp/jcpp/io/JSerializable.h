#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JObjectInputStream.h"
//#include "JObjectOutputStream.h"

class JSerializable:JObject{
protected:
    JSerializable();
public:

    static JClass* getClazz();

    //virtual void writeObject(JObjectOutputStream*);
    virtual void readObject(JObjectInputStream*);
};

#endif // JSERIALIZABLE_H
