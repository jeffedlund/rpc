#include "JException.h"
#include "JClass.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JExceptionClass : public JClass{
        public:
            JExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.Exception";
                name="java.lang.Exception";
                simpleName="Exception";
                serialVersionUID=-3387516993124229948ULL;
            }

            JClass* getSuperclass(){
                return JThrowable::getClazz();
            }

            JObject* newInstance(){
                return new JException();
            }
        };

        static JClass* clazz;

        JClass* JException::getClazz(){
            if (clazz==NULL){
                clazz=new JExceptionClass();
            }
            return clazz;
        }

        JException::JException():JThrowable(getClazz()){
        }

        JException::JException(JClass* _class):JThrowable(_class){
        }

        JException::JException(JString message):JThrowable(getClazz()){
            setMessage(new JString(message));
        }

        JException::JException(JString message, JThrowable *cause):JThrowable(getClazz()){
            setMessage(new JString(message));
            setCause(cause);
        }

        JException::~JException(){
        }
    }
}
