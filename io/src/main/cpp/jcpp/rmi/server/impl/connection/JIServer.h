#ifndef JISERVER_H
#define JISERVER_H

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
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIServer : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual JObject* lookup(JEndPoint* endPoint, JClass* clazz)=0;
                        virtual JIRegistry* getRegistry()=0;
                        virtual JIGC* getGC()=0;
                        virtual JIGCClient* getGCClient()=0;
                        virtual ~JIServer();
                    };
                }
            }
        }
    }
}
#endif // JISERVER_H
