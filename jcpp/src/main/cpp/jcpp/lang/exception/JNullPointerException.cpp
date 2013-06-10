#include "JNullPointerException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JNullPointerExceptionClass : public JClass{
        public:
            JNullPointerExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.NullPointerException";
                name="java.lang.NullPointerException";
                simpleName="NullPointerException";
                serialVersionUID=5162710183389028792ULL;
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

        JNullPointerException::JNullPointerException(JString message):JRuntimeException(getClazz()){
            setMessage(new JString(message));
        }

        JNullPointerException::~JNullPointerException(){
        }
    }
}
