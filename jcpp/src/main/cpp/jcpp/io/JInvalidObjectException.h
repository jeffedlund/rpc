#ifndef JINVALIDOBJECTEXCEPTION_H
#define JINVALIDOBJECTEXCEPTION_H

#include "JObjectStreamException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JInvalidObjectException : public JObjectStreamException{
        public:
            JInvalidObjectException();
            JInvalidObjectException(string message);

            static JClass* getClazz();
            virtual ~JInvalidObjectException();
        };
    }
}
#endif // JINVALIDOBJECTEXCEPTION_H
