#ifndef JNULLPOINTEREXCEPTION_H
#define JNULLPOINTEREXCEPTION_H
#include "JRuntimeException.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JNullPointerException : public JRuntimeException{

        public:
            JNullPointerException();
            JNullPointerException(string message);
            JNullPointerException(JString* message);

            static JClass* getClazz();
        };
    }
}

#endif // JNULLPOINTEREXCEPTION_H
