#include "JObjectStreamConstants.h"
#include "JInstantiationException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JObjectStreamConstantsClass : public JClass{
        public:
            JObjectStreamConstantsClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectStreamConstants";
                name="java.io.ObjectStreamConstants";
                simpleName="ObjectStreamConstants";
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JObjectStreamConstants::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectStreamConstantsClass();
            }
            return clazz;
        }
    }
}

