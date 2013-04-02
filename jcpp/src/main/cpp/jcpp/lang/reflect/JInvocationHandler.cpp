#include "JInvocationHandler.h"
#include "JClass.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JInvocationHandlerClass : public JClass{
            public:
                JInvocationHandlerClass():JClass(JClassLoader::getBootClassLoader()){
                    canonicalName="java.lang.reflect.InvocationHandler";
                    name="java.lang.reflect.InvocationHandler";
                    simpleName="InvocationHandler";
                    bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JInvocationHandler::getClazz(){
                if (clazz==NULL){
                    clazz= new JInvocationHandlerClass();
                }
                return clazz;
            }

            JInvocationHandler::~JInvocationHandler(){
            }
        }
    }
}
