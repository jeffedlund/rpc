#include "JClassCastException.h"

namespace jcpp{
    namespace lang{
        class JClassCastExceptionClass : public JClass{
        public:
            JClassCastExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.ClassCastException";
                name="java.lang.ClassCastException";
                simpleName="ClassCastException";
                serialVersionUID=-7034897190745766939ULL;
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

        JClassCastException::JClassCastException(string message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JClassCastException::~JClassCastException(){
        }
    }
}
