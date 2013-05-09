#include "JObjectOutput.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JObjectOutputClass : public JClass{
        public:
            JObjectOutputClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectOutput";
                name="java.io.ObjectOutput";
                simpleName="ObjectOutput";
                bIsInterface=true;
                addInterface(JDataOutput::getClazz());
                addInterface(JAutoCloseable::getClazz());
            }

            JClass* getSuperclass(){
                return JDataOutput::getClazz();//TODO can have several superclass... check what is the case in java
            }
        };

        static JClass* clazz;

        JClass* JObjectOutput::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectOutputClass();
            }
            return clazz;
        }

        JObjectOutput::~JObjectOutput(){
        }
    }
}



