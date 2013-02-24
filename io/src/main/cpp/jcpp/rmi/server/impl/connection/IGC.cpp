#include "JIGC.h"
#include "JSerializable.h"
#include "JInstantiationException.h"
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace impl{
                namespace connection{
                    class JIGCClass : public JClass{
                      public:
                        JIGCClass(){
                            this->canonicalName="jcpp.rmi.server.impl.connection.IGC";
                            this->name="jcpp.rmi.server.impl.connection.IGC";
                            this->simpleName="IGC";
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

                    JClass* JIGC::getClazz(){
                        if (clazz==NULL){
                            clazz=new JIGCClass();
                        }
                        return clazz;
                    }
                }
            }
        }
    }
}


