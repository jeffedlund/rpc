#ifndef JIOEXCEPTION_H
#define JIOEXCEPTION_H

#include "JException.h"
#include "JClass.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace io{
        class JCPP_LIBRARY_EXPORT JIOException : public JException{
        protected:
            JIOException(JClass* _class);

        public:
            JIOException();
            JIOException(JString message);
            static JClass* getClazz();
            virtual ~JIOException();
        };
    }
}

#endif // JIOEXCEPTION_H
