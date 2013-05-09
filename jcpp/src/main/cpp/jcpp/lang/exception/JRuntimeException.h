#ifndef JRUNTIMEEXCEPTION_H
#define JRUNTIMEEXCEPTION_H

#include "JException.h"
#include "JThrowable.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JRuntimeException : public JException{
        protected:
            JRuntimeException(JClass* _class);

        public:
            JRuntimeException();
            JRuntimeException(JString message);
            JRuntimeException(JString message,JThrowable* cause);

            static JClass* getClazz();
            virtual ~JRuntimeException();
        };
    }
}

#endif // JRUNTIMEEXCEPTION_H
