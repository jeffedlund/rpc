#ifndef JEOFEXCEPTION_H
#define JEOFEXCEPTION_H

#include "JIOException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JEOFException : public JIOException{
        public:
            JEOFException();
            JEOFException(JString message);
            static JClass* getClazz();
            virtual ~JEOFException();
        };
    }
}

#endif // JEOFEXCEPTION_H
