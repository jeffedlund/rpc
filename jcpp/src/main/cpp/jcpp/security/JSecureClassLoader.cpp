#include "JSecureClassLoader.h"
#include "JClass.h"

namespace jcpp{
    namespace security{
        class JSecureClassLoaderClass : public JClass{
            public:
                JSecureClassLoaderClass(){
                    this->canonicalName="java.security.SecureClassLoader";
                    this->name="java.security.SecureClassLoader";
                    this->simpleName="SecureClassLoader";
                }

                JClass* getSuperclass(){
                    return JClassLoader::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JSecureClassLoader::getClazz(){
            if (clazz==NULL){
                clazz=new JSecureClassLoaderClass();
            }
            return clazz;
        }

        JSecureClassLoader::JSecureClassLoader(JClass* _class,JClassLoader* parent):JClassLoader(_class,parent){
        }

        JSecureClassLoader::~JSecureClassLoader(){
        }
    }
}

