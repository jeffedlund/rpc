#ifndef JINVOCATIONHANDLER_H
#define JINVOCATIONHANDLER_H

#include "JObject.h"
#include "JMethod.h"
using namespace std;

class JInvocationHandler : public JObject{
public:
    virtual JObject *invoke(JObject* proxy, JMethod* method, vector<JObject*>* args) = 0;
};


#endif // JINVOCATIONHANDLER_H
