#include "JUTFDataFormatException.h"

JUTFDataFormatException::JUTFDataFormatException()
{
}

JUTFDataFormatException::JUTFDataFormatException(std::string message) : JException(message){
}

JUTFDataFormatException::JUTFDataFormatException(JUTFDataFormatException* e){
    this->setMessage(e->getMessage());
}
