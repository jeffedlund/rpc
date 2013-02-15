#include "JExternalizable.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JExternalizableClass : public JClass{
        public:
            JExternalizableClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.Externalizable";
                name="java.io.Externalizable";
                simpleName="Externalizable";
                serialVersionUID=0;
                bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
            }
        };

        static JClass* clazz;

        JClass* JExternalizable::getClazz(){
            if (clazz==NULL){
                clazz=new JExternalizableClass();
            }
            return clazz;
        }

    }
}
