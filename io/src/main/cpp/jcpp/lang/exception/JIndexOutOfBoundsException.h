#ifndef JINDEXOUTOFBOUNDSEXCEPTION_H
#define JINDEXOUTOFBOUNDSEXCEPTION_H

#include "JRuntimeException.h"
#include "JClass.h"
#include "JCPP.h"

using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JIndexOutOfBoundsException : public JRuntimeException{
        public:
            JIndexOutOfBoundsException();
            JIndexOutOfBoundsException(string message);
            JIndexOutOfBoundsException(JString* message);

            static JClass* getClazz();
            virtual ~JIndexOutOfBoundsException();
        };
    }
}

#endif // JINDEXOUTOFBOUNDSEXCEPTION_H
