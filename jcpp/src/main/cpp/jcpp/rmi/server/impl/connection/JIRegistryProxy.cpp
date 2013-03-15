#include "JIRegistryProxy.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
#include "JVoid.h"
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    JIRegistryProxy::JIRegistryProxyClass::JIRegistryProxyClass():JProxyClass(){
                        this->canonicalName="jcpp.rmi.server.impl.connection.IRegistryProxy";
                        this->name="jcpp.rmi.server.impl.connection.IRegistryProxy";
                        this->simpleName="IRegistryProxy";
                    }

                    JClass* JIRegistryProxy::JIRegistryProxyClass::getSuperclass(){
                        return JProxy::getClazz();
                    }

                    JObject* JIRegistryProxy::JIRegistryProxyClass::newInstance(){
                        return new JIRegistryProxy();
                    }

                    static JClass* clazz;

                    JClass* JIRegistryProxy::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIRegistryProxyClass();
                        }
                        return clazz;
                    }

                    JIRegistryProxy::JIRegistryProxy():JProxy(getClazz()){
                    }

                    void JIRegistryProxy::bind(JString* id, JObject* object, JPrimitiveArray* interfaces){
                        vector<JObject*> args;
                        args.push_back(id);
                        args.push_back(object);
                        args.push_back(interfaces);
                        invoke("bind",&args);
                    }

                    JPrimitiveArray* JIRegistryProxy::list(){
                        vector<JObject*> args;
                        return (JPrimitiveArray*)invoke("list",&args);
                    }

                    JObject* JIRegistryProxy::lookup(JString* id){
                        vector<JObject*> args;
                        args.push_back(id);
                        return (JObject*)invoke("lookup",&args);
                    }

                    void JIRegistryProxy::rebind(JString* id, JObject* object, JPrimitiveArray* interfaces){
                        vector<JObject*> args;
                        args.push_back(id);
                        args.push_back(object);
                        args.push_back(interfaces);
                        invoke("rebind",&args);
                    }

                    void JIRegistryProxy::unbind(JString* id){
                        vector<JObject*> args;
                        args.push_back(id);
                        invoke("unbind",&args);
                    }

                    JIRegistryProxy::~JIRegistryProxy(){
                    }
                }
            }
        }
    }
}

