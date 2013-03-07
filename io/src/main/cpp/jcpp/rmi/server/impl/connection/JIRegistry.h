#ifndef JIREGISTRY_H
#define JIREGISTRY_H


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
                    class JCPP_LIBRARY_EXPORT JIRegistry : public JInterface{
                    public:
                        static JClass* getClazz();
                        virtual void bind(JString* id, JObject* object, JPrimitiveArray* interfaces)=0;
                        virtual JPrimitiveArray* list()=0;
                        virtual JObject* lookup(JString* id)=0;
                        virtual void rebind(JString* id, JObject* object, JPrimitiveArray* interfaces)=0;
                        virtual void unbind(JString* id)=0;
                        virtual ~JIRegistry();
                    };
                }
            }
        }
    }
}
#endif // JIREGISTRY_H
