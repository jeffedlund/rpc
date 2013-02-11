#ifndef JINDEXOUTOFBOUNDSEXCEPTION_H
#define JINDEXOUTOFBOUNDSEXCEPTION_H

#include "JRuntimeException.h"
#include "JClass.h"

using namespace std;

namespace jcpp{
    namespace lang{
        class JIndexOutOfBoundsException : public JRuntimeException{
        public:
            JIndexOutOfBoundsException();
            JIndexOutOfBoundsException(string message);
            JIndexOutOfBoundsException(JString* message);

            static JClass* getClazz();
        };
    }
}

#endif // JINDEXOUTOFBOUNDSEXCEPTION_H
