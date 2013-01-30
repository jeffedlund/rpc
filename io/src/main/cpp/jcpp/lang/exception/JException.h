#ifndef JEXCEPTION_H
#define JEXCEPTION_H

#include "JObject.h"

class JException: public JObject {
    //TODO use all the fields of Java exception (getCause)

    std::string message;
    JException *cause;

public:
    JException();
    JException(std::string message);
    JException(std::string, JException *cause);

    static JClass* clazz;

    JException *getCause();
    void setMessage(std::string message);

    std::string getMessage();

    ~JException();
};


#endif // JEXCEPTION_H
