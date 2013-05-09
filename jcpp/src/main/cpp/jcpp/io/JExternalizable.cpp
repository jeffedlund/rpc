#include "JExternalizable.h"
#include "JInstantiationException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JExternalizableClass : public JClass{
        public:
            JExternalizableClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.Externalizable";
                name="java.io.Externalizable";
                simpleName="Externalizable";
                bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JSerializable::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JExternalizable::getClazz(){
            if (clazz==NULL){
                clazz=new JExternalizableClass();
            }
            return clazz;
        }

        JExternalizable::~JExternalizable(){
        }
    }
}
