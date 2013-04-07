#include "JIGCClientProxy.h"
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
                    JIGCClientProxy::JIGCClientProxyClass::JIGCClientProxyClass():JProxyClass(){
                        this->canonicalName="jcpp.rmi.server.impl.connection.IGCClientProxy";
                        this->name="jcpp.rmi.server.impl.connection.IGCClientProxy";
                        this->simpleName="IGCClientProxy";
                        this->bIsProxy=true;
                    }

                    JClass* JIGCClientProxy::JIGCClientProxyClass::getSuperclass(){
                        return JProxy::getClazz();
                    }

                    JObject* JIGCClientProxy::JIGCClientProxyClass::newInstance(){
                        return new JIGCClientProxy();
                    }

                    static JClass* clazz;

                    JClass* JIGCClientProxy::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCClientProxyClass();
                        }
                        return clazz;
                    }

                    JIGCClientProxy::JIGCClientProxy():JProxy(getClazz()){
                    }

                    JPrimitiveArray* JIGCClientProxy::getEndPoints(){
                        vector<JObject*> args;
                        return (JPrimitiveArray*)invoke("getEndPoints",&args);
                    }

                    JIGCClientProxy::~JIGCClientProxy(){
                    }
                }
            }
        }
    }
}



