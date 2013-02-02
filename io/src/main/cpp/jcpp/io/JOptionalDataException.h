#ifndef JOPTIONALDATAEXCEPTION_H
#define JOPTIONALDATAEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

class JOptionalDataException : public JObjectStreamException{
protected:
    JOptionalDataException(JClass* _clazz);
public:
    JOptionalDataException();
    JOptionalDataException(string message);

    static JClass* getClazz();
};

#endif // JOPTIONALDATAEXCEPTION_H