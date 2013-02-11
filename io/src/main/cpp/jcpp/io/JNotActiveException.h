#ifndef JNOTACTIVEEXCEPTION_H
#define JNOTACTIVEEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JNotActiveException : public JObjectStreamException{
        protected:
            JNotActiveException(JClass* _clazz);
        public:
            JNotActiveException();
            JNotActiveException(string message);

            static JClass* getClazz();
        };
    }
}

#endif // JNOTACTIVEEXCEPTION_H
