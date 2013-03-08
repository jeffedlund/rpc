#ifndef JILLEGALSTATEEXCEPTION_H
#define JILLEGALSTATEEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JIllegalStateException : public JRuntimeException
        {
        public:
            JIllegalStateException();
            JIllegalStateException(string message);

            static JClass* getClazz();
            virtual ~JIllegalStateException();
        };
    }
}

#endif // JILLEGALSTATEEXCEPTION_H
