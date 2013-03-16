#include "JIServerProxy.h"
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
                    JIServerProxy::JIServerProxyClass::JIServerProxyClass():JProxyClass(){
                        this->canonicalName="jcpp.rmi.server.impl.connection.IServerProxy";
                        this->name="jcpp.rmi.server.impl.connection.IServerProxy";
                        this->simpleName="IServerProxy";
                    }

                    JClass* JIServerProxy::JIServerProxyClass::getSuperclass(){
                        return JProxy::getClazz();
                    }

                    JObject* JIServerProxy::JIServerProxyClass::newInstance(){
                        return new JIServerProxy();
                    }

                    static JClass* clazz;

                    JClass* JIServerProxy::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIServerProxyClass();
                        }
                        return clazz;
                    }

                    JIServerProxy::JIServerProxy():JProxy(getClazz()){
                    }

                    JObject* JIServerProxy::lookup(JEndPoint* endPoint, JClass* clazz){
                        vector<JObject*> args;
                        args.push_back(endPoint);
                        args.push_back(clazz);
                        return invoke("lookup",&args);
                    }

                    JIRegistry* JIServerProxy::getIRegistry(){
                        vector<JObject*> args;
                        return (JIRegistry*)invoke("getIRegistry",&args);
                    }

                    JIGC* JIServerProxy::getGC(){
                        vector<JObject*> args;
                        return (JIGC*)invoke("getGC",&args);
                    }

                    JIGCClient* JIServerProxy::getGCClient(){
                        vector<JObject*> args;
                        return (JIGCClient*)invoke("getGCClient",&args);
                    }

                    JIServerProxy::~JIServerProxy(){
                    }
                }
            }
        }
    }
}


