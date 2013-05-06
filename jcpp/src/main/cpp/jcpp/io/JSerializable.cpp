#include "JSerializable.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JSerializableClass : public JClass{
        public:
            JSerializableClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.Serializable";
                name="java.io.Serializable";
                simpleName="Serializable";
                bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JSerializable::getClazz(){
            if (clazz==NULL){
                clazz=new JSerializableClass();
            }
            return clazz;
        }

        JSerializable::~JSerializable(){
        }
    }
}
