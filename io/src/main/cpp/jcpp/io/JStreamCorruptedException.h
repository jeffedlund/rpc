#ifndef JSTREAMCORRUPTEDEXCEPTION_H
#define JSTREAMCORRUPTEDEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JStreamCorruptedException : public JObjectStreamException{
        protected:
            JStreamCorruptedException(JClass* _clazz);
        public:
            JStreamCorruptedException();
            JStreamCorruptedException(string message);

            static JClass* getClazz();
        };
    }
}

#endif // JSTREAMCORRUPTEDEXCEPTION_H
