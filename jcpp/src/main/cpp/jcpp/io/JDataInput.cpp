#include "JDataInput.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JDataInputClass : public JClass{
        public:
            JDataInputClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.DataInput";
                name="java.io.DataInput";
                simpleName="DataInput";
                bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JDataInput::getClazz(){
            if (clazz==NULL){
                clazz=new JDataInputClass();
            }
            return clazz;
        }

        JDataInput::~JDataInput(){
        }
    }
}

