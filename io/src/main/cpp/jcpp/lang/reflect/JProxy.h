#ifndef JPROXY_H
#define JPROXY_H

#include "JObject.h"
#include "JInvocationHandler.h"

//TODO
class JProxy : public JObject
{
    JInvocationHandler *invocationHandler;

public:
    static JClass* clazz;

    JProxy();

    JObject* invoke(){return NULL;}

    JInvocationHandler* getInvocationHandler();
    void setInvocationHandler(JInvocationHandler* invocationHandler);

    std::vector<std::string>* getInterfaces();
    bool isProxy();

    ~JProxy();
};

#endif // JPROXY_H
