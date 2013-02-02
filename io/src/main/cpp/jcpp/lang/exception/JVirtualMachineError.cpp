#include "JVirtualMachineError.h"
#include "JClass.h"

class JVirtualMachineErrorClass : public JClass{
public:
    JVirtualMachineErrorClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.VirtualMachineError";
        name="java.lang.VirtualMachineError";
        simpleName="VirtualMachineError";
        serialVersionUID=4980196508277280342L;
    }

    JClass* getSuperclass(){
        return JError::getClazz();
    }

    JObject* newInstance(){
        return new JVirtualMachineError();
    }
};

static JClass* clazz;

JClass* JVirtualMachineError::getClazz(){
    if (clazz==NULL){
        clazz=new JVirtualMachineErrorClass();
    }
    return clazz;
}

JVirtualMachineError::JVirtualMachineError():JError(getClazz()){
}

JVirtualMachineError::JVirtualMachineError(JClass* _class):JError(_class){
}

JVirtualMachineError::JVirtualMachineError(std::string message):JError(getClazz()){
    this->message = message;
}

JVirtualMachineError::JVirtualMachineError(std::string message, JThrowable *cause):JError(getClazz()){
    this->message = message;
    this->cause = cause;
}

JVirtualMachineError::~JVirtualMachineError(){
}

