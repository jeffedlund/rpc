#ifndef JCLONENOTSUPPORTEDEXCEPTION_H
#define JCLONENOTSUPPORTEDEXCEPTION_H

#include "JException.h"
#include "JThrowable.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JCloneNotSupportedException : public JException{
        protected:
            JCloneNotSupportedException(JClass* _class);

        public:
            JCloneNotSupportedException();
            JCloneNotSupportedException(JString message);
            JCloneNotSupportedException(JString message,JThrowable* cause);
            static JClass* getClazz();
            virtual ~JCloneNotSupportedException();
        };
    }
}

#endif // JCLONENOTSUPPORTEDEXCEPTION_H
