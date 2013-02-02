#ifndef JINTERNALERROR_H
#define JINTERNALERROR_H

#include "JObject.h"
#include "JVirtualMachineError.h"
using namespace std;

class JInternalError : public JVirtualMachineError {
protected:
    JInternalError(JClass* _class);

public:
    JInternalError();
    JInternalError(string message);
    JInternalError(string message, JThrowable *cause);

    static JClass* getClazz();

    ~JInternalError();
};

#endif // JINTERNALERROR_H
