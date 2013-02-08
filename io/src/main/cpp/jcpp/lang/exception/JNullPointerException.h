#ifndef JNULLPOINTEREXCEPTION_H
#define JNULLPOINTEREXCEPTION_H
#include "JRuntimeException.h"
using namespace std;

class JNullPointerException : public JRuntimeException{

public:
    JNullPointerException();
    JNullPointerException(string message);
    JNullPointerException(JString* message);

    static JClass* getClazz();
};

#endif // JNULLPOINTEREXCEPTION_H
