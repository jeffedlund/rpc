#ifndef JINVALIDCLASSEXCEPTION_H
#define JINVALIDCLASSEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

class JInvalidClassException : public JObjectStreamException{
public:
    JInvalidClassException();
    JInvalidClassException(string message);

     static JClass* getClazz();
};

#endif // JINVALIDCLASSEXCEPTION_H
