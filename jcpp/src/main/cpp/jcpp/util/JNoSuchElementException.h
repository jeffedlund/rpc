#ifndef JNOSUCHELEMENTEXCEPTION_H
#define JNOSUCHELEMENTEXCEPTION_H

#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JNoSuchElementException : public JRuntimeException{

        public:
            JNoSuchElementException();
            JNoSuchElementException(JString message);
            JNoSuchElementException(JString* message);

            static JClass* getClazz();
            virtual ~JNoSuchElementException();
        };
    }
}

#endif // JNOSUCHELEMENTEXCEPTION_H
