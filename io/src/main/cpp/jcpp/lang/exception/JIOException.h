#ifndef JIOEXCEPTION_H
#define JIOEXCEPTION_H
#include "JException.h"

class JIOException : public JException
{
public:
    JIOException();
    JIOException(std::string message);
    JIOException(JIOException* e);
};

#endif // JIOEXCEPTION_H
