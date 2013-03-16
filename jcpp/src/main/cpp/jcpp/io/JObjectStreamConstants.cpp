#include "JObjectStreamConstants.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JObjectStreamConstantsClass : public JClass{
        public:
            JObjectStreamConstantsClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectStreamConstants";
                name="java.io.ObjectStreamConstants";
                simpleName="ObjectStreamConstants";
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
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

