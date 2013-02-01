#ifndef JILLEGALARGUMENTEXCEPTION_H
#define JILLEGALARGUMENTEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
using namespace std;

class JIllegalArgumentException : public JRuntimeException
{
public:
    JIllegalArgumentException();
    JIllegalArgumentException(string message);
    JIllegalArgumentException(string message,JThrowable* cause);

    static JClass* getClazz();
};

#endif // JILLEGALARGUMENTEXCEPTION_H
