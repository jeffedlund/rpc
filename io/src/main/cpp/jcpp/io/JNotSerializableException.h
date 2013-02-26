#ifndef JNOTSERIALIZABLEEXCEPTION_H
#define JNOTSERIALIZABLEEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JNotSerializableException : public JObjectStreamException{
        protected:
            JNotSerializableException(JClass* _clazz);
        public:
            JNotSerializableException();
            JNotSerializableException(string message);

            static JClass* getClazz();
            virtual ~JNotSerializableException();
        };
    }
}

#endif // JNOTSERIALIZABLEEXCEPTION_H
