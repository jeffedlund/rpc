#include "JError.h"
#include "JClass.h"

class JErrorClass : public JClass{
public:
    JErrorClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.Error";
        name="java.lang.Error";
        simpleName="Error";
        serialVersionUID=4980196508277280342L;
    }

    JClass* getSuperclass(){
        return JThrowable::getClazz();
    }

    JObject* newInstance(){
        return new JError();
    }
};

static JClass* clazz;

JClass* JError::getClazz(){
    if (clazz==NULL){
        clazz=new JErrorClass();
    }
    return clazz;
}

JError::JError():JThrowable(getClazz()){
}

JError::JError(JClass* _class):JThrowable(_class){
}

JError::JError(std::string message):JThrowable(getClazz()){
    this->message = message;
}

JError::JError(std::string message, JThrowable *cause):JThrowable(getClazz()){
    this->message = message;
    this->cause = cause;
}

JError::~JError(){
}