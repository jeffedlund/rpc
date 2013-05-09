#include "JBits.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JBitsClass : public JClass{
        public:
            JBitsClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.Bits";
                name="java.io.Bits";
                simpleName="Bits";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JBits::getClazz(){
            if (clazz==NULL){
                clazz=new JBitsClass();
            }
            return clazz;
        }
    }
}

