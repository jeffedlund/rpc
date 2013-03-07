#ifndef JINVALIDCLASSEXCEPTION_H
#define JINVALIDCLASSEXCEPTION_H

#include "JObjectStreamException.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JInvalidClassException : public JObjectStreamException{
        public:
            JInvalidClassException();
            JInvalidClassException(string message);

             static JClass* getClazz();
             virtual ~JInvalidClassException();
        };
    }
}

#endif // JINVALIDCLASSEXCEPTION_H
