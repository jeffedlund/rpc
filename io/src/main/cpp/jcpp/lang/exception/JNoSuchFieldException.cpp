#include "JNoSuchFieldException.h"

class JNoSuchFieldExceptionClass : public JClass{
public:
    JNoSuchFieldExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.NoSuchFieldException";
        name="java.lang.NoSuchFieldException";
        simpleName="NoSuchFieldException";
        serialVersionUID=-3387516993124229948L;
    }

    JClass* getSuperclass(){
        return JException::getClazz();
    }

    JObject* newInstance(){
        return new JNoSuchFieldException();
    }
};

static JClass* clazz;

JClass* JNoSuchFieldException::getClazz(){
    if (clazz==NULL){
        clazz=new JNoSuchFieldExceptionClass();
    }
    return clazz;
}

JNoSuchFieldException::JNoSuchFieldException():JException(getClazz()){
}

JNoSuchFieldException::JNoSuchFieldException(string message):JException(getClazz()){
    this->message=new JString(message);
}
