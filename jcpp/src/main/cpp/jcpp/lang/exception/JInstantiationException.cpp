#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        class JInstantiationExceptionClass : public JClass{
        public:
            JInstantiationExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.InstantiationException";
                name="java.lang.InstantiationException";
                simpleName="InstantiationException";
                serialVersionUID=-8441929162975509110ULL;
            }

            JClass* getSuperclass(){
                return JException::getClazz();
            }

            JObject* newInstance(){
                return new JInstantiationException();
            }
        };

        static JClass* clazz;

        JClass* JInstantiationException::getClazz(){
            if (clazz==NULL){
                clazz=new JInstantiationExceptionClass();
            }
            return clazz;
        }

        JInstantiationException::JInstantiationException():JException(getClazz()){
        }

        JInstantiationException::JInstantiationException(string message):JException(getClazz()){
            this->message=new JString(message);
        }

        JInstantiationException::~JInstantiationException(){
        }
    }
}

