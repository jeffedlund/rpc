#ifndef JINVOCATIONHANDLER_H
#define JINVOCATIONHANDLER_H

#include "JObject.h"
#include "JMethod.h"

//TODO
class JInvocationHandler
{
public:
    virtual JObject *invoke(JObject *proxy, JMethod method, JObject *args[]) = 0;
};


#endif // MINVOCATIONHANDLER_H
