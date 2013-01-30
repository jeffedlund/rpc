#include "JException.h"
#include "JClass.h"

class JExceptionClass : public JClass{
};

JClass* JException::clazz=new JExceptionClass();

JException::JException():JObject(clazz){
    cause = NULL;
}

JException::JException(std::string message):JObject(clazz){
    this->message = message;
    cause = NULL;
}

JException::JException(std::string message, JException *cause):JObject(clazz){
    this->message = message;
    this->cause = cause;
}

JException *JException::getCause() {
    return cause;
}

void JException::setMessage(std::string message){
    this->message = message;
}

std::string JException::getMessage(){
    return this->message;
}

JException::~JException(){
}
