#ifndef JVIRTUALMACHINEERROR_H
#define JVIRTUALMACHINEERROR_H

#include "JObject.h"
#include "JError.h"
using namespace std;

class JVirtualMachineError : public JError {
protected:
    JVirtualMachineError(JClass* _class);

public:
    JVirtualMachineError();
    JVirtualMachineError(string message);
    JVirtualMachineError(string message, JThrowable *cause);

    static JClass* getClazz();

    ~JVirtualMachineError();
};

#endif // JVIRTUALMACHINEERROR_H
