#include "JIGCProxy.h"
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
                    JIGCProxy::JIGCProxyClass::JIGCProxyClass():JProxyClass(){
                        this->canonicalName="jcpp.rmi.server.impl.connection.IGCProxy";
                        this->name="jcpp.rmi.server.impl.connection.IGCProxy";
                        this->simpleName="IGCProxy";
                    }

                    JClass* JIGCProxy::JIGCProxyClass::getSuperclass(){
                        return JProxy::getClazz();
                    }

                    JObject* JIGCProxy::JIGCProxyClass::newInstance(){
                        return new JIGCProxy();
                    }

                    static JClass* clazz;

                    JClass* JIGCProxy::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCProxyClass();
                        }
                        return clazz;
                    }

                    JIGCProxy::JIGCProxy():JProxy(getClazz()){
                    }

                    JPrimitiveArray* JIGCProxy::ping(JEndPoint* endPoint, JPrimitiveArray* id){
                        vector<JObject*> args;
                        args.push_back(endPoint);
                        args.push_back(id);
                        return (JPrimitiveArray*)invoke("ping",&args);
                    }

                    void JIGCProxy::endPointDead(JEndPoint* endPoint){
                        vector<JObject*> args;
                        args.push_back(endPoint);
                        invoke("endPointDead",&args);
                    }

                    JPrimitiveArray* JIGCProxy::getExportedEndPoints(){
                        vector<JObject*> args;
                        return (JPrimitiveArray*)invoke("getExportedEndPoints",&args);
                    }

                    JIGCProxy::~JIGCProxy(){
                    }
                }
            }
        }
    }
}


