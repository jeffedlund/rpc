#ifndef JSERIALIZABLE_H
#define JSERIALIZABLE_H

#include "JObject.h"
#include "JClass.h"
#include "JInterface.h"

class JSerializable : public JInterface{
protected:
    JSerializable();
public:

    static JClass* getClazz();
};

#endif // JSERIALIZABLE_H
