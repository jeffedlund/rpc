#ifndef JSTREAMCORRUPTEDEXCEPTION_H
#define JSTREAMCORRUPTEDEXCEPTION_H

#include "JObjectStreamException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JStreamCorruptedException : public JObjectStreamException{
        protected:
            JStreamCorruptedException(JClass* _clazz);
        public:
            JStreamCorruptedException();
            JStreamCorruptedException(JString message);
            static JClass* getClazz();
            virtual ~JStreamCorruptedException();
        };
    }
}

#endif // JSTREAMCORRUPTEDEXCEPTION_H
