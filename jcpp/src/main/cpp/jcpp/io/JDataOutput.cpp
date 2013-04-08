#include "JDataOutput.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace io{
        class JDataOutputClass : public JClass{
        public:
            JDataOutputClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.DataOutput";
                name="java.io.DataOutput";
                simpleName="DataOutput";
                bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JDataOutput::getClazz(){
            if (clazz==NULL){
                clazz=new JDataOutputClass();
            }
            return clazz;
        }

        JDataOutput::~JDataOutput(){
        }
    }
}


