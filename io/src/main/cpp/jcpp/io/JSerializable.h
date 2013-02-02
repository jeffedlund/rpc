#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
#include "JObjectInputStream.h"
//#include "JObjectOutputStream.h"

class JSerializable{
public:

    //virtual void writeObject(JObjectOutputStream*);
    virtual void readObject(JObjectInputStream*);
};

#endif // JSERIALIZABLE_H
