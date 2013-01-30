#ifndef JEOFEXCEPTION_H
#define JEOFEXCEPTION_H
#include "JException.h"

class JEOFException : public JException
{
public:
    JEOFException();
    JEOFException(std::string message);
    JEOFException(JEOFException* e);
};

#endif // JEOFEXCEPTION_H
