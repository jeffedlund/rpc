#ifndef JVIRTUALMACHINEERROR_H
#define JVIRTUALMACHINEERROR_H

#include "JObject.h"
#include "JError.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JVirtualMachineError : public JError {
        protected:
            JVirtualMachineError(JClass* _class);

        public:
            JVirtualMachineError();
            JVirtualMachineError(string message);
            JVirtualMachineError(string message, JThrowable *cause);

            static JClass* getClazz();

            virtual ~JVirtualMachineError();
        };
    }
}

#endif // JVIRTUALMACHINEERROR_H
