#ifndef JRUNTIMEEXCEPTION_H
#define JRUNTIMEEXCEPTION_H

#include "JException.h"
#include "JThrowable.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JRuntimeException : public JException{
        protected:
            JRuntimeException(JClass* _class);

        public:
            JRuntimeException();
            JRuntimeException(string message);
            JRuntimeException(string message,JThrowable* cause);

            static JClass* getClazz();
        };
    }
}

#endif // JRUNTIMEEXCEPTION_H
