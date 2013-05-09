#ifndef JNOTSERIALIZABLEEXCEPTION_H
#define JNOTSERIALIZABLEEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JNotSerializableException : public JObjectStreamException{
        protected:
            JNotSerializableException(JClass* _clazz);
        public:
            JNotSerializableException();
            JNotSerializableException(JString message);
            static JClass* getClazz();
            virtual ~JNotSerializableException();
        };
    }
}

#endif // JNOTSERIALIZABLEEXCEPTION_H
