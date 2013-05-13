#ifndef JUNSUPPORTEDOPERATIONEXCEPTION_H
#define JUNSUPPORTEDOPERATIONEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{

        class JCPP_LIBRARY_EXPORT JUnsupportedOperationException : public JRuntimeException{
        protected:
            JUnsupportedOperationException(JClass* _class);
        public:
            JUnsupportedOperationException();
            JUnsupportedOperationException(JString message);
            static JClass* getClazz();
            virtual ~JUnsupportedOperationException();
        };
    }
}

#endif // JUNSUPPORTEDOPERATIONEXCEPTION_H
