#include "JConcurrentModificationException.h"

namespace jcpp{
    namespace util{
        class JConcurrentModificationExceptionClass : public JClass{
        public:
            JConcurrentModificationExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.util.ConcurrentModificationException";
                name="java.util.ConcurrentModificationException";
                simpleName="ConcurrentModificationException";
                serialVersionUID=3666751008965953603ULL;
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JConcurrentModificationException();
            }
        };

        static JClass* clazz;

        JClass* JConcurrentModificationException::getClazz(){
            if (clazz==NULL){
                clazz=new JConcurrentModificationExceptionClass();
            }
            return clazz;
        }

        JConcurrentModificationException::JConcurrentModificationException():JRuntimeException(getClazz()){
        }

        JConcurrentModificationException::JConcurrentModificationException(string message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JConcurrentModificationException::JConcurrentModificationException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JConcurrentModificationException::~JConcurrentModificationException(){
        }
    }
}


