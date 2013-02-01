#ifndef JNOSUCHFIELDEXCEPTION_H
#define JNOSUCHFIELDEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;

class JNoSuchFieldException : public JException
{
public:
    JNoSuchFieldException();
    JNoSuchFieldException(string message);

    static JClass* getClazz();
};

#endif // JNOSUCHFIELDEXCEPTION_H
