#ifndef JIGCCLIENTPROXY_H
#define JIGCCLIENTPROXY_H

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
#include "JIGCClient.h"
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
                    class JCPP_LIBRARY_EXPORT JIGCClientProxy : public JProxy, public JIGCClient{
                    protected:
                        class JCPP_LIBRARY_EXPORT JIGCClientProxyClass : public JProxyClass {
                        public:
                            JIGCClientProxyClass();
                            virtual JClass* getSuperclass();
                            virtual JObject* newInstance();
                        };
                    public:
                        JIGCClientProxy();
                        static JClass* getClazz();
                        virtual JPrimitiveArray* getEndPoints();
                        virtual ~JIGCClientProxy();
                    };
                }
            }
        }
    }
}

#endif // JIGCCLIENTPROXY_H
