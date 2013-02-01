#include "JNoSuchMethodException.h"

class JNoSuchMethodExceptionClass : public JClass{
public:
    JNoSuchMethodExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.NoSuchMethodException";
        name="java.lang.NoSuchMethodException";
        simpleName="NoSuchMethodException";
        serialVersionUID=-3387516993124229948L;
    }

    JClass* getSuperclass(){
        return JException::getClazz();
    }

    JObject* newInstance(){
        return new JNoSuchMethodException();
    }
};

static JClass* clazz;

JClass* JNoSuchMethodException::getClazz(){
    if (clazz==NULL){
        clazz=new JNoSuchMethodExceptionClass();
    }
    return clazz;
}

JNoSuchMethodException::JNoSuchMethodException():JException(getClazz()){
}

JNoSuchMethodException::JNoSuchMethodException(string message):JException(getClazz()){
    this->message=message;
}

