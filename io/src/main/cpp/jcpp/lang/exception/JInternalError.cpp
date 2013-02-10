#include "JInternalError.h"
#include "JClass.h"

class JInternalErrorClass : public JClass{
public:
    JInternalErrorClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.InternalError";
        name="java.lang.InternalError";
        simpleName="InternalError";
        serialVersionUID=4980196508277280342ULL;
    }

    JClass* getSuperclass(){
        return JError::getClazz();
    }

    JObject* newInstance(){
        return new JInternalError();
    }
};

static JClass* clazz;

JClass* JInternalError::getClazz(){
    if (clazz==NULL){
        clazz=new JInternalErrorClass();
    }
    return clazz;
}

JInternalError::JInternalError():JVirtualMachineError(getClazz()){
}

JInternalError::JInternalError(JClass* _class):JVirtualMachineError(_class){
}

JInternalError::JInternalError(std::string message):JVirtualMachineError(getClazz()){
    this->message = new JString(message);
}

JInternalError::JInternalError(std::string message, JThrowable *cause):JVirtualMachineError(getClazz()){
    this->message = new JString(message);
    this->cause = cause;
}

JInternalError::~JInternalError(){
}


