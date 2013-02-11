#include "JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JRuntimeExceptionClass : public JClass{
        public:
            JRuntimeExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.RuntimeException";
                name="java.lang.RuntimeException";
                simpleName="RuntimeException";
                serialVersionUID=-7034897190745766939ULL;
            }

            JClass* getSuperclass(){
                return JException::getClazz();
            }

            JObject* newInstance(){
                return new JRuntimeException();
            }
        };

        static JClass* clazz;

        JClass* JRuntimeException::getClazz(){
            if (clazz==NULL){
                clazz=new JRuntimeExceptionClass();
            }
            return clazz;
        }

        JRuntimeException::JRuntimeException():JException(getClazz()){
        }

        JRuntimeException::JRuntimeException(JClass* _class):JException(_class){
        }

        JRuntimeException::JRuntimeException(string message):JException(getClazz()){
            this->message=new JString(message);
        }

        JRuntimeException::JRuntimeException(string message,JThrowable* cause):JException(getClazz()){
            this->message=new JString(message);
            this->cause=cause;
        }
    }
}

