#include "JInterface.h"
#include "JClass.h"
#include "JClassLoader.h"
#include <sstream>
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        class JInterfaceClass : public JClass{
            public:
                JInterfaceClass():JClass(){
                    canonicalName="java.lang.Interface";
                    name="java.lang.Interface";//bof...
                    simpleName="Interface";
                    bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return NULL;
                }
        };

        static JClass* clazz;

        JClass* JInterface::getClazz(){
            if (clazz==NULL){
                clazz=new JInterfaceClass();
            }
            return clazz;
        }

        JInterface::~JInterface(){
        }
    }
}

