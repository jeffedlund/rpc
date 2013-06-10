#include "JClassCastException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JClassCastExceptionClass : public JClass{
        public:
            JClassCastExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.ClassCastException";
                name="java.lang.ClassCastException";
                simpleName="ClassCastException";
                serialVersionUID=-9223365651070458532ULL;
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JClassCastException();
            }
        };

        static JClass* clazz;

        JClass* JClassCastException::getClazz(){
            if (clazz==NULL){
                clazz=new JClassCastExceptionClass();
            }
            return clazz;
        }

        JClassCastException::JClassCastException():JRuntimeException(getClazz()){
        }

        JClassCastException::JClassCastException(JString message):JRuntimeException(getClazz()){
            setMessage(new JString(message));
        }

        JClassCastException::~JClassCastException(){
        }
    }
}
