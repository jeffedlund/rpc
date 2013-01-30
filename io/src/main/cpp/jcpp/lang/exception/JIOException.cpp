#include "JIOException.h"

JIOException::JIOException()
{
}


JIOException::JIOException(std::string message) : JException(message){
}

JIOException::JIOException(JIOException* e){
    this->setMessage(e->getMessage());
}
