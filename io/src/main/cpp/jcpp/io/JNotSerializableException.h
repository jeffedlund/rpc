#ifndef JNOTSERIALIZABLEEXCEPTION_H
#define JNOTSERIALIZABLEEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

//TODO add private serializable field int length, boolean eof
class JNotSerializableException : public JObjectStreamException{
protected:
    JNotSerializableException(JClass* _clazz);
public:
    JNotSerializableException();
    JNotSerializableException(string message);

    static JClass* getClazz();
};

#endif // JNOTSERIALIZABLEEXCEPTION_H
