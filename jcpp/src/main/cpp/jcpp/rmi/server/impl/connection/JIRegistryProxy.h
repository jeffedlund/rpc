#ifndef JIREGISTRYPROXY_H
#define JIREGISTRYPROXY_H


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
                    class JCPP_LIBRARY_EXPORT JIRegistryProxy : public JProxy, public JIRegistry{
                    protected:
                        class JCPP_LIBRARY_EXPORT JIRegistryProxyClass : public JProxyClass {
                        public:
                            JIRegistryProxyClass();
                            virtual JClass* getSuperclass();
                            virtual JObject* newInstance();
                        };
                    public:
                        JIRegistryProxy();
                        static JClass* getClazz();
                        virtual void bind(JString* id, JObject* object, JPrimitiveArray* interfaces);
                        virtual JPrimitiveArray* list();
                        virtual JObject* lookup(JString* id);
                        virtual void rebind(JString* id, JObject* object, JPrimitiveArray* interfaces);
                        virtual void unbind(JString* id);
                        virtual ~JIRegistryProxy();
                    };
                }
            }
        }
    }
}

#endif // JIREGISTRYPROXY_H
