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
                class JCPP_LIBRARY_EXPORT JProxyClass : public JClass{
                public:
                    JProxyClass();
                    virtual JClass* getSuperclass();
                    virtual JObject* newInstance();
                };

                JInvocationHandler *invocationHandler;
                JProxy(JClass* _class);

            public:
                JProxy();
                JProxy(JInvocationHandler* i);
                static JClass* getClazz();
                static JClass* getProxyClass(vector<JClass*>* interfaces);
                static JProxy* newProxyInstance(vector<JClass*>* interfaces, JInvocationHandler* i);
                static jbool isProxyClass(JClass* cl);
                static JInvocationHandler* getInvocationHandler(JObject* proxy);
                virtual JInvocationHandler* getInvocationHandler();
                virtual void setInvocationHandler(JInvocationHandler* invocationHandler);
                virtual JObject* invoke(JString method, vector<JObject*>* args);
                virtual jint hashCode();
                virtual jbool equals(JObject *o);
                virtual JString toString();
                virtual ~JProxy();
            };
        }
    }
}

#endif // JPROXY_H
