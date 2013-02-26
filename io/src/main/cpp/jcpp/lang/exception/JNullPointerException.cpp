#include "JNullPointerException.h"

namespace jcpp{
    namespace lang{
        class JNullPointerExceptionClass : public JClass{
        public:
            JNullPointerExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.NullPointerException";
                name="java.lang.NullPointerException";
                simpleName="NullPointerException";
                serialVersionUID=-7034897190745766939ULL;
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JNullPointerException();
            }
        };

        static JClass* clazz;

        JClass* JNullPointerException::getClazz(){
            if (clazz==NULL){
                clazz=new JNullPointerExceptionClass();
            }
            return clazz;
        }

        JNullPointerException::JNullPointerException():JRuntimeException(getClazz()){
        }

        JNullPointerException::JNullPointerException(string message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JNullPointerException::JNullPointerException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JNullPointerException::~JNullPointerException(){
        }
    }
}
