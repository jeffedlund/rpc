#ifndef JARRAYINDEXOUTOFBOUNDSEXCEPTION_H
#define JARRAYINDEXOUTOFBOUNDSEXCEPTION_H

#include "JIndexOutOfBoundsException.h"
#include "JClass.h"
#include "JCPP.h"

using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JArrayIndexOutOfBoundsException : public JIndexOutOfBoundsException {
        public:
            JArrayIndexOutOfBoundsException();
            JArrayIndexOutOfBoundsException(string message);
            JArrayIndexOutOfBoundsException(JString* message);

            static JClass* getClazz();
            virtual ~JArrayIndexOutOfBoundsException();
        };
    }
}
#endif // JARRAYINDEXOUTOFBOUNDSEXCEPTION_H
