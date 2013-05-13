#ifndef JNOSUCHFIELDEXCEPTION_H
#define JNOSUCHFIELDEXCEPTION_H

#include "JException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JNoSuchFieldException : public JException
        {
        public:
            JNoSuchFieldException();
            JNoSuchFieldException(JString message);
            static JClass* getClazz();
            virtual ~JNoSuchFieldException();
        };
    }
}

#endif // JNOSUCHFIELDEXCEPTION_H
