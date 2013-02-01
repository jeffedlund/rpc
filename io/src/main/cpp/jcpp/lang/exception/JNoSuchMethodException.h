#ifndef JNOSUCHMETHODEXCEPTION_H
#define JNOSUCHMETHODEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;

class JNoSuchMethodException : public JException
{
public:
    JNoSuchMethodException();
    JNoSuchMethodException(string message);

    static JClass* getClazz();
};

#endif // JNOSUCHMETHODEXCEPTION_H
