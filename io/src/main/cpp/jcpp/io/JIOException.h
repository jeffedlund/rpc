#ifndef JIOEXCEPTION_H
#define JIOEXCEPTION_H

#include "JException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JIOException : public JException{
        protected:
            JIOException(JClass* _class);

        public:
            JIOException();
            JIOException(string message);

            static JClass* getClazz();
        };
    }
}

#endif // JIOEXCEPTION_H
