#include "JOptionalDataException.h"

class JOptionalDataExceptionClass : public JClass{
public:
    JOptionalDataExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.OptionalDataException";
        name="java.io.OptionalDataException";
        simpleName="OptionalDataException";
        serialVersionUID=-8011121865681257820ULL;
    }

    JClass* getSuperclass(){
        return JObjectStreamException::getClazz();
    }

    JObject* newInstance(){
        return new JOptionalDataException();
    }
};

static JClass* clazz;

JClass* JOptionalDataException::getClazz(){
    if (clazz==NULL){
        clazz=new JOptionalDataExceptionClass();
    }
    return clazz;
}

JOptionalDataException::JOptionalDataException(JClass* _class):JObjectStreamException(_class){
}

JOptionalDataException::JOptionalDataException():JObjectStreamException(getClazz()){
}

JOptionalDataException::JOptionalDataException(string message) : JObjectStreamException(getClazz()){
    this->message=new JString(message);
}


