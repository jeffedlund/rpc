#include "JIRegistry.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIRegistryClass : public JClass{
                      public:
                        JIRegistryClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IRegistry";
                            this->name="jcpp.rmi.server.impl.connection.IRegistry";
                            this->simpleName="IRegistry";
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

                    JClass* JIRegistry::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIRegistryClass();
                        }
                        return clazz;
                    }
                }
            }
        }
    }
}
