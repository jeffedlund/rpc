#ifndef JILLEGALARGUMENTEXCEPTION_H
#define JILLEGALARGUMENTEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JIllegalArgumentException : public JRuntimeException
        {
        public:
            JIllegalArgumentException();
            JIllegalArgumentException(string message);
            JIllegalArgumentException(string message,JThrowable* cause);

            static JClass* getClazz();
            virtual ~JIllegalArgumentException();
        };
    }
}

#endif // JILLEGALARGUMENTEXCEPTION_H
