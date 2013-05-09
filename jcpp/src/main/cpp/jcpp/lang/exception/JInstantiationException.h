#ifndef JINSTANTIATIONEXCEPTION_H
#define JINSTANTIATIONEXCEPTION_H

#include "JException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JInstantiationException : public JException{
        public:
            JInstantiationException();
            JInstantiationException(JString message);
            static JClass* getClazz();
            virtual ~JInstantiationException();
        };
    }
}

#endif // JINSTANTIATIONEXCEPTION_H
