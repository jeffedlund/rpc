#include "JIGCClient.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIGCClientClass : public JClass{
                    protected:
                        static JObject* invokeGetEndPoints(JObject* object,vector<JObject*>*){
                            JIGCClient* gcClient=dynamic_cast<JIGCClient*>(object);
                            return gcClient->getEndPoints();
                        }

                      public:
                        JIGCClientClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IGCClient";
                            this->name="jcpp.rmi.server.impl.connection.IGCClient";
                            this->simpleName="IGCClient";
                            this->bIsInterface=true;

                            vector<JClass*>* param=new vector<JClass*>();
                            addMethod(new JMethod("getEndPoints",this,JPrimitiveArray::getClazz(JEndPoint::getClazz()),param,invokeGetEndPoints));
                        }

                        JClass* getSuperclass(){
                            return JInterface::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JIGCClient::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCClientClass();
                        }
                        return clazz;
                    }

                    JIGCClient::~JIGCClient(){
                    }
                }
            }
        }
    }
}
