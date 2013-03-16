#ifndef JISERVERPROXY_H
#define JISERVERPROXY_H

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
#include "JIServer.h"
#include "JProxy.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JCPP_LIBRARY_EXPORT JIServerProxy : public JProxy, public JIServer{
                    protected:
                        class JIServerProxyClass : public JProxyClass {
                        public:
                            JIServerProxyClass();
                            virtual JClass* getSuperclass();
                            virtual JObject* newInstance();
                        };
                    public:
                        JIServerProxy();
                        static JClass* getClazz();
                        virtual JObject* lookup(JEndPoint* endPoint, JClass* clazz);
                        virtual JIRegistry* getIRegistry();
                        virtual JIGC* getGC();
                        virtual JIGCClient* getGCClient();
                        virtual ~JIServerProxy();
                    };
                }
            }
        }
    }
}

#endif // JISERVERPROXY_H
