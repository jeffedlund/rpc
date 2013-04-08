#include "JObjectInput.h"

namespace jcpp{
    namespace io{
        class JObjectInputClass : public JClass{
        public:
            JObjectInputClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectInput";
                name="java.io.ObjectInput";
                simpleName="ObjectInput";
                bIsInterface=true;
                addInterface(JDataInput::getClazz());
                addInterface(JAutoCloseable::getClazz());
            }

            JClass* getSuperclass(){
                return JDataInput::getClazz();//TODO can have several superclass... check what is the case in java
            }
        };

        static JClass* clazz;

        JClass* JObjectInput::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectInputClass();
            }
            return clazz;
        }

        JObjectInput::~JObjectInput(){
        }
    }
}


