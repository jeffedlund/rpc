#ifndef JOBJECTHANDLER_H
#define JOBJECTHANDLER_H

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
#include "JIRegistry.h"
#include "JIGCClient.h"
#include "JIGC.h"
#include "JILifecycle.h"
#include "JInvocationHandler.h"
#include "JClassLoader.h"
#include "JIInvocationListener.h"
#include "JObjectPointer.h"
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
                    class JInvoker;
                    class JObjectInformations;
                    class JCPP_LIBRARY_EXPORT JObjectHandler: public JObject, public JInvocationHandler, public JSerializable, public JCloneable{
                    protected:
                        JInvoker* invoker;
                        JObject* proxy;
                        JClassLoader* classLoader;
                        JPrimitiveArray* pinterfaces;
                        JIInvocationListener* invocationListener;
                        friend class JObjectHandlerClass;

                    public:
                        JObjectHandler();
                        JObjectHandler(JObjectInformations* objectInformations,vector<JClass*>* interfaces, JObjectPointer* objectPointer);
                        static JClass* getClazz();
                        JObject* getProxy();
                        JInvoker* getInvoker();
                        JClassLoader* getClassLoader();
                        vector<JClass*>* getInterfaces();
                        virtual JObject* invoke(JObject* proxy, JMethod* method, vector<JObject*>* args);
                        void setObjectInformations(JObjectInformations* objectInformations);
                        virtual string toString();
                        virtual jint hashCode();
                        virtual jbool equals(JObject *o);
                        virtual JObject* clone();
                        virtual ~JObjectHandler();
                    };
                }
            }
        }
    }
}
#endif // JOBJECTHANDLER_H
