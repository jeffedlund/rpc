#include "JIllegalArgumentException.h"


class JIllegalArgumentExceptionClass : public JClass{
public:
    JIllegalArgumentExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.IllegalArgumentException";
        name="java.lang.IllegalArgumentException";
        simpleName="IllegalArgumentException";
        serialVersionUID=-5365630128856068164ULL;
    }

    JClass* getSuperclass(){
        return JRuntimeException::getClazz();
    }

    JObject* newInstance(){
        return new JIllegalArgumentException();
    }
};

static JClass* clazz;

JClass* JIllegalArgumentException::getClazz(){
    if (clazz==NULL){
        clazz=new JIllegalArgumentExceptionClass();
    }
    return clazz;
}

JIllegalArgumentException::JIllegalArgumentException():JRuntimeException(getClazz()){
}

JIllegalArgumentException::JIllegalArgumentException(string message):JRuntimeException(getClazz()){
    this->message=new JString(message);
}


