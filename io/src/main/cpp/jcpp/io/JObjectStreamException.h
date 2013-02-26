#ifndef JOBJECTSTREAMEXCEPTION_H
#define JOBJECTSTREAMEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JObjectStreamException : public JIOException{
        protected:
            JObjectStreamException(JClass* _clazz);
        public:
            JObjectStreamException();
            JObjectStreamException(string message);

             static JClass* getClazz();

             virtual ~JObjectStreamException();
        };
    }
}

#endif // JOBJECTSTREAMEXCEPTION_H
