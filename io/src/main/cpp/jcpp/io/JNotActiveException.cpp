#include "JNotActiveException.h"

class JNotActiveExceptionClass : public JClass{
public:
    JNotActiveExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.NotActiveException";
        name="java.io.NotActiveException";
        simpleName="NotActiveException";
        serialVersionUID=-3893467273049808895ULL;
    }

    JClass* getSuperclass(){
        return JObjectStreamException::getClazz();
    }

    JObject* newInstance(){
        return new JNotActiveException();
    }
};

static JClass* clazz;

JClass* JNotActiveException::getClazz(){
    if (clazz==NULL){
        clazz=new JNotActiveExceptionClass();
    }
    return clazz;
}

JNotActiveException::JNotActiveException(JClass* _class):JObjectStreamException(_class){
}

JNotActiveException::JNotActiveException():JObjectStreamException(getClazz()){
}

JNotActiveException::JNotActiveException(string message) : JObjectStreamException(getClazz()){
    this->message=new JString(message);
}


