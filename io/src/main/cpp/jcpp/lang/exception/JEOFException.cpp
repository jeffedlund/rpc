#include "JEOFException.h"

JEOFException::JEOFException(){
}

JEOFException::JEOFException(std::string message) : JException(message){
}

JEOFException::JEOFException(JEOFException* e){
    this->setMessage(e->getMessage());
}
