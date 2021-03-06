#include "JUnsupportedOperationException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JUnsupportedOperationExceptionClass : public JClass{
        public:
            JUnsupportedOperationExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.UnsupportedOperationException";
                name="java.lang.UnsupportedOperationException";
                simpleName="UnsupportedOperationException";
                serialVersionUID=-1242599979055084673ULL;
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JUnsupportedOperationException();
            }
        };

        static JClass* clazz;

        JClass* JUnsupportedOperationException::getClazz(){
            if (clazz==NULL){
                clazz=new JUnsupportedOperationExceptionClass();
            }
            return clazz;
        }

        JUnsupportedOperationException::JUnsupportedOperationException(JClass* _class):JRuntimeException(_class){
        }

        JUnsupportedOperationException::JUnsupportedOperationException():JRuntimeException(getClazz()){
        }

        JUnsupportedOperationException::JUnsupportedOperationException(JString message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JUnsupportedOperationException::~JUnsupportedOperationException(){
        }
    }
}



