#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
//#include "MObjectInputStream.h"
//#include "MObjectOutputStream.h"

class JSerializable{
public:
    bool isSerializable() const {
        return true;
    }

  //  virtual void writeObject(MObjectOutputStream*) = 0;
  //  virtual void readObject(MObjectInputStream*) = 0;
};

#endif // JSERIALIZABLE_H
