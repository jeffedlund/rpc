#ifndef JUNSUPPORTEDOPERATIONEXCEPTION_H
#define JUNSUPPORTEDOPERATIONEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
using namespace std;

class JUnsupportedOperationException : public JRuntimeException
{
public:
    JUnsupportedOperationException();
    JUnsupportedOperationException(string message);
    JUnsupportedOperationException(string message,JThrowable* cause);

    static JClass* getClazz();
};

#endif // JUNSUPPORTEDOPERATIONEXCEPTION_H
