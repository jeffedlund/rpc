#ifndef JCLASSCASTEXCEPTION_H
#define JCLASSCASTEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
using namespace std;

class JClassCastException : public JRuntimeException
{
public:
    JClassCastException();
    JClassCastException(string message);

    static JClass* getClazz();
};

#endif // JCLASSCASTEXCEPTION_H
