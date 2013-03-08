#ifndef JNULLPOINTEREXCEPTION_H
#define JNULLPOINTEREXCEPTION_H

#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JNullPointerException : public JRuntimeException{

        public:
            JNullPointerException();
            JNullPointerException(string message);
            JNullPointerException(JString* message);

            static JClass* getClazz();
            virtual ~JNullPointerException();
        };
    }
}

#endif // JNULLPOINTEREXCEPTION_H
