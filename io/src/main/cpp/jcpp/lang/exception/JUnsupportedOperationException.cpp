#include "JUnsupportedOperationException.h"


class JUnsupportedOperationExceptionClass : public JClass{
public:
    JUnsupportedOperationExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.UnsupportedOperationException";
        name="java.lang.UnsupportedOperationException";
        simpleName="UnsupportedOperationException";
        serialVersionUID=-1242599979055084673ULL;
    }

    JClass* getSuperclass(){
        return JRuntimeException::getClazz();
    }

    JObject* newInstance(){
        return new JUnsupportedOperationException();
    }
};

static JClass* clazz;

JClass* JUnsupportedOperationException::getClazz(){
    if (clazz==NULL){
        clazz=new JUnsupportedOperationExceptionClass();
    }
    return clazz;
}

JUnsupportedOperationException::JUnsupportedOperationException():JRuntimeException(getClazz()){
}

JUnsupportedOperationException::JUnsupportedOperationException(string message):JRuntimeException(getClazz()){
    this->message=new JString(message);
}



