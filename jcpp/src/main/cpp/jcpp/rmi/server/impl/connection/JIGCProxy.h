#ifndef JIGCPROXY_H
#define JIGCPROXY_H

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
#include "JIGC.h"
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
                    class JCPP_LIBRARY_EXPORT JIGCProxy : public JProxy, public JIGC{
                    protected:
                        class JCPP_LIBRARY_EXPORT JIGCProxyClass : public JProxyClass {
                        public:
                            JIGCProxyClass();
                            virtual JClass* getSuperclass();
                            virtual JObject* newInstance();
                        };
                    public:
                        JIGCProxy();
                        static JClass* getClazz();
                        virtual JPrimitiveArray* ping(JEndPoint* endPoint, JPrimitiveArray* id);
                        virtual void endPointDead(JEndPoint* endPoint);
                        virtual JPrimitiveArray* getExportedEndPoints();
                        virtual ~JIGCProxy();
                    };
                }
            }
        }
    }
}

#endif // JIGCPROXY_H
