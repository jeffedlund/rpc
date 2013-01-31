#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
#include "JObjectInputStream.h"
//#include "MObjectOutputStream.h"

class JSerializable{
public:
    bool isSerializable() const {
        return true;
    }

    //virtual void writeObject(MObjectOutputStream*);
    virtual void readObject(JObjectInputStream*);
};

#endif // JSERIALIZABLE_H
