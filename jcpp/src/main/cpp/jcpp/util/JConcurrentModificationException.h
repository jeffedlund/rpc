#ifndef JCONCURRENTMODIFICATIONEXCEPTION_H
#define JCONCURRENTMODIFICATIONEXCEPTION_H


#include "JRuntimeException.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JConcurrentModificationException : public JRuntimeException{

        public:
            JConcurrentModificationException();
            JConcurrentModificationException(string message);
            JConcurrentModificationException(JString* message);

            static JClass* getClazz();
            virtual ~JConcurrentModificationException();
        };
    }
}
#endif // JCONCURRENTMODIFICATIONEXCEPTION_H
