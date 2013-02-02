#ifndef JEOFEXCEPTION_H
#define JEOFEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
using namespace std;

class JEOFException : public JIOException{
public:
    JEOFException();
    JEOFException(string message);

    static JClass* getClazz();
};

#endif // JEOFEXCEPTION_H