#include "JCloneNotSupportedException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JCloneNotSupportedExceptionClass : public JClass{
        public:
            JCloneNotSupportedExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.CloneNotSupportedException";
                name="java.lang.CloneNotSupportedException";
                simpleName="CloneNotSupportedException";
                serialVersionUID=5195511250079656443ULL;
            }

            JClass* getSuperclass(){
                return JException::getClazz();
            }

            JObject* newInstance(){
                return new JCloneNotSupportedException();
            }
        };

        static JClass* clazz;

        JClass* JCloneNotSupportedException::getClazz(){
            if (clazz==NULL){
                clazz=new JCloneNotSupportedExceptionClass();
            }
            return clazz;
        }

        JCloneNotSupportedException::JCloneNotSupportedException():JException(getClazz()){
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JClass* _class):JException(_class){
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JString message):JException(getClazz()){
            setMessage(new JString(message));
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JString message,JThrowable* cause):JException(getClazz()){
            setMessage(new JString(message));
            setCause(cause);
        }

        JCloneNotSupportedException::~JCloneNotSupportedException(){
        }
    }
}


