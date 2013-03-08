#include "JITransportRouter.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JITransportRouterClass : public JClass{
                      public:
                        JITransportRouterClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.ITransportRouter";
                            this->name="jcpp.rmi.server.impl.transport.ITransportRouter";
                            this->simpleName="ITransportRouter";
                            this->bIsInterface=true;
                        }

                        JClass* getSuperclass(){
                            return JInterface::getClazz();
                        }

                        JObject* newInstance(){
                            throw new JInstantiationException("cannot instantiate object of class "+getName());
                        }
                    };

                    static JClass* clazz;

                    JClass* JITransportRouter::getClazz(){
                        if (clazz==NULL){
                            clazz=new JITransportRouterClass();
                        }
                        return clazz;
                    }

                    JITransportRouter::~JITransportRouter(){
                    }
                }
            }
        }
    }
}
