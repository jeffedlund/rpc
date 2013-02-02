#ifndef JPROXY_H
#define JPROXY_H

#include "JObject.h"
#include "JInvocationHandler.h"
using namespace std;

class JProxy : public JObject{
    JInvocationHandler *invocationHandler;
    vector<JClass*>* interfaces;

public:
    JProxy();

    JInvocationHandler* getInvocationHandler();
    void setInvocationHandler(JInvocationHandler* invocationHandler);

    vector<JClass*>* getInterfaces();
    void setInterfaces(vector<JClass*>* interfaces);

    static JClass* getClazz();

    JObject* invoke(string method, vector<JObject*>* args);

    string toString();

    ~JProxy();
};

#endif // JPROXY_H
