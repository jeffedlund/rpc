#ifndef JPROXY_H
#define JPROXY_H

#include "JObject.h"
#include "JInvocationHandler.h"
#include "JCPP.h"
using namespace std;


namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_LIBRARY_EXPORT JProxy : public JObject{
            protected:
                class JProxyClass : public JClass{
                public:
                    JProxyClass();
                    virtual JClass* getSuperclass();
                    virtual JObject* newInstance();
                };

                JInvocationHandler *invocationHandler;
                vector<JClass*>* interfaces;
                JProxy(JClass* _class);

            public:
                JProxy();
                JProxy(vector<JClass*>* interfaces, JInvocationHandler* i);
                static JClass* getProxyClass(vector<JClass*>* interfaces);
                static JProxy* create(vector<JClass*>* interfaces, JInvocationHandler* i);

                JInvocationHandler* getInvocationHandler();
                void setInvocationHandler(JInvocationHandler* invocationHandler);

                vector<JClass*>* getInterfaces();
                void setInterfaces(vector<JClass*>* interfaces);

                static JClass* getClazz();

                JObject* invoke(string method, vector<JObject*>* args);

                string toString();

                virtual ~JProxy();
            };
        }
    }
}

#endif // JPROXY_H
