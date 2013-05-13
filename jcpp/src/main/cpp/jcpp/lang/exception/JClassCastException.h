#ifndef JCLASSCASTEXCEPTION_H
#define JCLASSCASTEXCEPTION_H

#include "JException.h"
#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JClassCastException : public JRuntimeException
        {
        public:
            JClassCastException();
            JClassCastException(JString message);
            static JClass* getClazz();
            virtual ~JClassCastException();
        };
    }
}

#endif // JCLASSCASTEXCEPTION_H
