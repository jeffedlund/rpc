#include "JITransportDispatcher.h"
#include "JSerializable.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace transport{
                    class JITransportDispatcherClass : public JClass{
                      public:
                        JITransportDispatcherClass(){
                            this->canonicalName="jcpp.rmi.server.impl.transport.ITransportDispatcher";
                            this->name="jcpp.rmi.server.impl.transport.ITransportDispatcher";
                            this->simpleName="ITransportDispatcher";
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

                    JClass* JITransportDispatcher::getClazz(){
                        if (clazz==NULL){
                            clazz=new JITransportDispatcherClass();
                        }
                        return clazz;
                    }

                    JITransportDispatcher::~JITransportDispatcher(){
                    }
                }
            }
        }
    }
}

