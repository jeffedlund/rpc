#include "JModifier.h"
#include "JClass.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JModifierClass : public JClass{
            public:
                JModifierClass():JClass(JClassLoader::getBootClassLoader()){
                    canonicalName="java.lang.reflect.Modifier";
                    name="java.lang.reflect.Modifier";
                    simpleName="Modifier";
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JModifier::getClazz(){
                if (clazz==NULL){
                    clazz= new JModifierClass();
                }
                return clazz;
            }

            jint JModifier::PUBLIC = 0x00000001;

            jint JModifier::PRIVATE = 0x00000002;

            jint JModifier::PROTECTED = 0x00000004;

            jint JModifier::STATIC = 0x00000008;

            jint JModifier::FINAL = 0x00000010;

            jint JModifier::SYNCHRONIZED = 0x00000020;

            jint JModifier::VOLATILE = 0x00000040;

            jint JModifier::TRANSIENT = 0x00000080;

            jint JModifier::NATIVE = 0x00000100;

            jint JModifier::INTERFACE = 0x00000200;

            jint JModifier::ABSTRACT = 0x00000400;

            jint JModifier::STRICT = 0x00000800;

            static jint BRIDGE    = 0x00000040;
            static jint VARARGS   = 0x00000080;
            static jint SYNTHETIC = 0x00001000;
            static jint ANNOTATION  = 0x00002000;
            static jint ENUM      = 0x00004000;
            static jint SYNTHESIZED = 0x00010000;

            jbool JModifier::isSynthetic(jint mod) {
                return (mod & SYNTHETIC) != 0;
            }

            jbool JModifier::isPublic(jint mod){
                return (mod & PUBLIC) !=0;
            }

            JModifier::~JModifier(){
            }
        }
    }
}


