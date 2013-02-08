#include "JThrowable.h"
#include "JClass.h"
#include "Collections.h"
#include "JString.h"

static JObject* getDetailMessage(JObject* object){
    JThrowable* th=(JThrowable*)object;
    return th->getMessage();
}

static void setDetailMessage(JObject* object,JObject* value){
    JThrowable* th=(JThrowable*)object;
    th->setMessage((JString*)value);
}

static JObject* getCause(JObject* object){
    JThrowable* th=(JThrowable*)object;
    return th->getCause();
}

static void setCause(JObject* object,JObject* value){
    JThrowable* th=(JThrowable*)object;
    th->setCause((JThrowable*)value);
}

static JObject* getStackTrace(JObject* object){
    JThrowable* th=(JThrowable*)object;
    return th->getStackTrace();
}


static void setStackTrace(JObject* object,JObject* value){
    JThrowable* th=(JThrowable*)object;
    th->setStackTrace((JPrimitiveArray*)value);
}

class JThrowableClass : public JClass{
public:
    JThrowableClass():JClass(JClassLoader::getBootClassLoader()){
        canonicalName="java.lang.Throwable";
        name="java.lang.Throwable";
        simpleName="Throwable";
        serialVersionUID=-3042686055658047285L;
        addField(new JField("detailMessage",JString::getClazz(),getDetailMessage,setDetailMessage));
        addField(new JField("cause",this,getCause,setCause));
        addField(new JField("stackTrace",JPrimitiveArray::getClazz(JStackTraceElement::getClazz()),getStackTrace,setStackTrace));
        addInterface(JSerializable::getClazz());
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
    this->message=NULL;
    this->cause=NULL;
    this->stackTrace=NULL;
}

JThrowable::JThrowable():JObject(getClazz()){
    this->message=NULL;
    this->cause=NULL;
    this->stackTrace=NULL;
}

JThrowable::JThrowable(string message):JObject(getClazz()){
    this->message = new JString(message);
    this->cause=NULL;
    this->stackTrace=NULL;
}

JThrowable::JThrowable(JString* message):JObject(getClazz()){
    this->message = message;
    this->cause=NULL;
    this->stackTrace=NULL;
}

JThrowable::JThrowable(string message, JThrowable *cause):JObject(getClazz()){
    this->message = new JString(message);
    this->cause = cause;
    this->stackTrace=NULL;
}

JThrowable::JThrowable(JString* message, JThrowable *cause):JObject(getClazz()){
    this->message = message;
    this->cause = cause;
    this->stackTrace=NULL;
}

bool JThrowable::operator==(JThrowable &other){
    return (other.message==message && other.cause==cause && other.stackTrace==stackTrace);
}

JThrowable *JThrowable::getCause() {
    return cause;
}

void JThrowable::setCause(JThrowable* cause) {
    this->cause=cause;
}

void JThrowable::setMessage(JString* message){
    this->message = message;
}

JString* JThrowable::getMessage(){
    return this->message;
}

JPrimitiveArray* JThrowable::getStackTrace(){
    return stackTrace;
}

void JThrowable::setStackTrace(JPrimitiveArray* stackTrace){
    this->stackTrace=stackTrace;
}

void JThrowable::printStackTrace(ostream* os){
    string str=toString()+"\r\n";
    os->write(str.c_str(),str.size());
    if (stackTrace!=NULL){
        for (int i=0;i<stackTrace->size();i++){
            JStackTraceElement* s=(JStackTraceElement*)stackTrace->get(i);
            string str="\tat "+s->toString()+"\r\n";
            os->write(str.c_str(),str.size());
        }
        if (getCause()!=NULL){
            string str="\r\nCaused by:\r\n";
            os->write(str.c_str(),str.size());
            getCause()->printStackTrace(os);
        }
    }
}

string JThrowable::toString(){
    return getClass()->getName()+":"+message->getString();
}

JThrowable::~JThrowable(){
    delete stackTrace;
    delete cause;
    delete message;
}

