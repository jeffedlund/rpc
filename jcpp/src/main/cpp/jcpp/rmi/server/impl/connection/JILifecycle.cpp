#include "JILifecycle.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JILifecycleClass : public JClass{
                      public:
                        JILifecycleClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.ILifecycle";
                            this->name="jcpp.rmi.server.impl.connection.ILifecycle";
                            this->simpleName="ILifecycle";
                            this->bIsInterface=true;
                        }

                        JClass* getSuperclass(){
                            return JInterface::getClazz();
                        }
                    };

                    static JClass* clazz;

                    JClass* JILifecycle::getClazz(){
                        if (clazz==NULL){
                            clazz=new JILifecycleClass();
                        }
                        return clazz;
                    }

                    JILifecycle::~JILifecycle(){
                    }
                }
            }
        }
    }
}

