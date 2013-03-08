#include "JIServer.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIServerClass : public JClass{
                      public:
                        JIServerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IServer";
                            this->name="jcpp.rmi.server.impl.connection.IServer";
                            this->simpleName="IServer";
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

                    JClass* JIServer::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIServerClass();
                        }
                        return clazz;
                    }

                    JIServer::~JIServer(){
                    }
                }
            }
        }
    }
}

