#ifndef JEXCEPTION_H
#define JEXCEPTION_H

#include "JObject.h"
#include "JThrowable.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JException: public JThrowable {
        protected:
            JException(JClass* _class);

        public:
            JException();
            JException(string message);
            JException(string message, JThrowable *cause);

            static JClass* getClazz();

            virtual ~JException();
        };
    }
}


#endif // JEXCEPTION_H
