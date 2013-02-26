#ifndef JUNSUPPORTEDOPERATIONEXCEPTION_H
#define JUNSUPPORTEDOPERATIONEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
using namespace std;

namespace jcpp{
    namespace lang{

        class JUnsupportedOperationException : public JRuntimeException
        {
        public:
            JUnsupportedOperationException();
            JUnsupportedOperationException(string message);
            JUnsupportedOperationException(string message,JThrowable* cause);

            static JClass* getClazz();
            virtual ~JUnsupportedOperationException();
        };
    }
}

#endif // JUNSUPPORTEDOPERATIONEXCEPTION_H
