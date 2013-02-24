#ifndef JREGISTRY_H
#define JREGISTRY_H

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
#include "JObjectInformations.h"
using namespace std;
using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::rmi::server::impl::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JRegistry: public JObject, public JIRegistry{
                    protected:
                        JObjectInformations* objectInformations;

                    public:
                        JRegistry(JObjectInformations* objectInformations);
                        static JClass* getClazz();
                        virtual void bind(JString* id, JObject* object, vector<JClass*>* interfaces);
                        virtual vector<JString*>* list();
                        virtual JObject* lookup(JString* id);
                        virtual void rebind(JString* id, JObject* object, vector<JClass*>* interfaces);
                        virtual void unbind(JString* id);
                        ~JRegistry();
                    };
                }
            }
        }
    }
}
#endif // JREGISTRY_H
