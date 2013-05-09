#ifndef JOBJECTSTREAMEXCEPTION_H
#define JOBJECTSTREAMEXCEPTION_H

#include "JIOException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JObjectStreamException : public JIOException{
        protected:
            JObjectStreamException(JClass* _clazz);
        public:
            JObjectStreamException();
            JObjectStreamException(JString message);
            static JClass* getClazz();
            virtual ~JObjectStreamException();
        };
    }
}

#endif // JOBJECTSTREAMEXCEPTION_H
