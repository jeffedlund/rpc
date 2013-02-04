#ifndef JILLEGALSTATEEXCEPTION_H
#define JILLEGALSTATEEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
using namespace std;

class JIllegalStateException : public JRuntimeException
{
public:
    JIllegalStateException();
    JIllegalStateException(string message);

    static JClass* getClazz();
};

#endif // JILLEGALSTATEEXCEPTION_H
