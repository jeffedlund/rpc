#ifndef JUTFDATAFORMATEXCEPTION_H
#define JUTFDATAFORMATEXCEPTION_H
#include "JException.h"

class JUTFDataFormatException : public JException
{
public:
    JUTFDataFormatException();
    JUTFDataFormatException(std::string message);
    JUTFDataFormatException(JUTFDataFormatException*);
};

#endif // JUTFDATAFORMATEXCEPTION_H
