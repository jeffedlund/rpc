#ifndef JNOSUCHMETHODEXCEPTION_H
#define JNOSUCHMETHODEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JNoSuchMethodException : public JException
        {
        public:
            JNoSuchMethodException();
            JNoSuchMethodException(string message);

            static JClass* getClazz();
            virtual ~JNoSuchMethodException();
        };
    }
}

#endif // JNOSUCHMETHODEXCEPTION_H
