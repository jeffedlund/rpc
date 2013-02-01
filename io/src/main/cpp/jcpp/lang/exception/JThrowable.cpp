#include "JThrowable.h"
#include "JClass.h"
#include "Collections.h"

class JThrowableClass : public JClass{
public:
    JThrowableClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.Throwable";
        name="java.lang.Throwable";
        simpleName="Throwable";
        serialVersionUID=-3042686055658047285L;
    }

    JClass* getSuperclass(){
        return JObject::getClazz();
    }

    JObject* newInstance(){
        return new JThrowable();
    }
};

static JClass* clazz;

JClass* JThrowable::getClazz(){
    if (clazz==NULL){
        clazz=new JThrowableClass();
    }
    return clazz;
}

JThrowable::JThrowable(JClass* _class):JObject(_class){
}

JThrowable::JThrowable():JObject(getClazz()){
}

JThrowable::JThrowable(string message):JObject(getClazz()){
    this->message = message;
}

JThrowable::JThrowable(string message, JThrowable *cause):JObject(getClazz()){
    this->message = message;
    this->cause = cause;
}

JThrowable *JThrowable::getCause() {
    return cause;
}

void JThrowable::setCause(JThrowable* cause) {
    this->cause=cause;
}

void JThrowable::setMessage(string message){
    this->message = message;
}

string JThrowable::getMessage(){
    return this->message;
}

vector<JStackTraceElement*>* JThrowable::getStackTrace(){
    return stackTrace;
}

void JThrowable::setStackTrace(vector<JStackTraceElement*>* stackTrace){
    this->stackTrace=stackTrace;
}


JThrowable::~JThrowable(){
    deleteVectorOfPointers(stackTrace);
}

