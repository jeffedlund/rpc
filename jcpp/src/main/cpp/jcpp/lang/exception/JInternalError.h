#ifndef JINTERNALERROR_H
#define JINTERNALERROR_H

#include "JObject.h"
#include "JVirtualMachineError.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JInternalError : public JVirtualMachineError {
        protected:
            JInternalError(JClass* _class);

        public:
            JInternalError();
            JInternalError(JString message);
            JInternalError(JString message, JThrowable *cause);

            static JClass* getClazz();

            virtual ~JInternalError();
        };
    }
}

#endif // JINTERNALERROR_H
