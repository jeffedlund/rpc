#ifndef JNOTACTIVEEXCEPTION_H
#define JNOTACTIVEEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JNotActiveException : public JObjectStreamException{
        protected:
            JNotActiveException(JClass* _clazz);
        public:
            JNotActiveException();
            JNotActiveException(JString message);
            static JClass* getClazz();
            virtual ~JNotActiveException();
        };
    }
}

#endif // JNOTACTIVEEXCEPTION_H
