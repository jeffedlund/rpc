#include "JAccessibleObject.h"
#include "JClass.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JAccessibleObjectClass : public JClass{
            public:
                JAccessibleObjectClass():JClass(JClassLoader::getBootClassLoader()){
                    canonicalName="java.lang.reflect.AccessibleObject";
                    name="java.lang.reflect.AccessibleObject";
                    simpleName="AccessibleObject";
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                JObject* newInstance(){
                    throw new JInstantiationException("cannot instantiate object of class "+getName());
                }
            };

            static JClass* clazz;

            JClass* JAccessibleObject::getClazz(){
                if (clazz==NULL){
                    clazz= new JAccessibleObjectClass();
                }
                return clazz;
            }

            JAccessibleObject::JAccessibleObject(JClass* clazz):JObject(clazz){
            }

            JAccessibleObject::~JAccessibleObject(){
            }
        }
    }
}

