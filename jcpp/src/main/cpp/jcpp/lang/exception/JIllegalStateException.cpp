#include "JIllegalStateException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JIllegalStateExceptionClass : public JClass{
        public:
            JIllegalStateExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.IllegalStateException";
                name="java.lang.IllegalStateException";
                simpleName="IllegalStateException";
                serialVersionUID=-1848914673093119416ULL;
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JIllegalStateException();
            }
        };

        static JClass* clazz;

        JClass* JIllegalStateException::getClazz(){
            if (clazz==NULL){
                clazz=new JIllegalStateExceptionClass();
            }
            return clazz;
        }

        JIllegalStateException::JIllegalStateException(JClass* _class):JRuntimeException(_class){
        }

        JIllegalStateException::JIllegalStateException():JRuntimeException(getClazz()){
        }

        JIllegalStateException::JIllegalStateException(JString message):JRuntimeException(getClazz()){
            setMessage(new JString(message));
        }

        JIllegalStateException::~JIllegalStateException(){
        }
    }
}


