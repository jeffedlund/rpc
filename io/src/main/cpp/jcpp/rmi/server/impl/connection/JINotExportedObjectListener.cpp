#include "JINotExportedObjectListener.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JINotExportedObjectListenerClass : public JClass{
                      public:
                        JINotExportedObjectListenerClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.INotExportedObjectListener";
                            this->name="jcpp.rmi.server.impl.connection.INotExportedObjectListener";
                            this->simpleName="INotExportedObjectListener";
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

                    JClass* JINotExportedObjectListener::getClazz(){
                        if (clazz==NULL){
                            clazz=new JINotExportedObjectListenerClass();
                        }
                        return clazz;
                    }
                }
            }
        }
    }
}


