#include "JEOFException.h"

class JEOFExceptionClass : public JClass{
public:
    JEOFExceptionClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.io.EOFException";
        name="java.io.EOFException";
        simpleName="EOFException";
        serialVersionUID=7818375828146090155ULL;
    }

    JClass* getSuperclass(){
        return JIOException::getClazz();
    }

    JObject* newInstance(){
        return new JEOFException();
    }
};

static JClass* clazz;

JClass* JEOFException::getClazz(){
    if (clazz==NULL){
        clazz=new JEOFExceptionClass();
    }
    return clazz;
}

JEOFException::JEOFException():JIOException(getClazz()){
}

JEOFException::JEOFException(string message) : JIOException(getClazz()){
    this->message=new JString(message);
}
