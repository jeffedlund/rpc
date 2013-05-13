#ifndef JNOSUCHMETHODEXCEPTION_H
#define JNOSUCHMETHODEXCEPTION_H

#include "JException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JNoSuchMethodException : public JException
        {
        public:
            JNoSuchMethodException();
            JNoSuchMethodException(JString message);
            static JClass* getClazz();
            virtual ~JNoSuchMethodException();
        };
    }
}

#endif // JNOSUCHMETHODEXCEPTION_H
