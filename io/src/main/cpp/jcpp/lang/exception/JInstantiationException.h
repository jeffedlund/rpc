#ifndef JINSTANTIATIONEXCEPTION_H
#define JINSTANTIATIONEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;

class JInstantiationException : public JException
{
public:
    JInstantiationException();
    JInstantiationException(string message);

    static JClass* getClazz();
};

#endif // JINSTANTIATIONEXCEPTION_H
