#ifndef JIINVOCATIONLISTENER_H
#define JIINVOCATIONLISTENER_H

#include "JObject.h"
#include "JClass.h"
#include <vector>
#include <iostream>
#include "JPrimitiveInt.h"
#include "JString.h"
#include "Object.h"
#include "JSerializable.h"
#include "JAddress.h"
#include "JDataInputStream.h"
#include "JDataOutputStream.h"
#include "JEndPoint.h"
#include "JException.h"
#include "JBoolean.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JCPP_LIBRARY_EXPORT JIInvocationListener : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual void invocationSucceeded(JObject* proxy, JMethod* method, vector<JObject*>* args)=0;
                        virtual void invocationFailed(JObject* proxy, JMethod* method, vector<JObject*>* args, JThrowable* e)=0;
                        virtual ~JIInvocationListener();
                    };
                }
            }
        }
    }
}

#endif // JIINVOCATIONLISTENER_H
