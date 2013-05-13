#ifndef JVIRTUALMACHINEERROR_H
#define JVIRTUALMACHINEERROR_H

#include "JObject.h"
#include "JError.h"
#include "JCPP.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JCPP_LIBRARY_EXPORT JVirtualMachineError : public JError {
        protected:
            JVirtualMachineError(JClass* _class);

        public:
            JVirtualMachineError();
            JVirtualMachineError(JString message);
            JVirtualMachineError(JString message, JThrowable *cause);
            static JClass* getClazz();
            virtual ~JVirtualMachineError();
        };
    }
}

#endif // JVIRTUALMACHINEERROR_H
