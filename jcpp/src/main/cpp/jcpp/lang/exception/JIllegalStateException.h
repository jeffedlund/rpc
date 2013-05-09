#ifndef JILLEGALSTATEEXCEPTION_H
#define JILLEGALSTATEEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JIllegalStateException : public JRuntimeException{
        protected:
            JIllegalStateException(JClass* _class);
        public:
            JIllegalStateException();
            JIllegalStateException(JString message);

            static JClass* getClazz();
            virtual ~JIllegalStateException();
        };
    }
}

#endif // JILLEGALSTATEEXCEPTION_H
