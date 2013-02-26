#ifndef JINVALIDCLASSEXCEPTION_H
#define JINVALIDCLASSEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JInvalidClassException : public JObjectStreamException{
        public:
            JInvalidClassException();
            JInvalidClassException(string message);

             static JClass* getClazz();
             virtual ~JInvalidClassException();
        };
    }
}

#endif // JINVALIDCLASSEXCEPTION_H
