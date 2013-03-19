#include "JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace lang{
        class JIndexOutOfBoundsExceptionClass : public JClass{
        public:
            JIndexOutOfBoundsExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.IndexOutOfBoundsException";
                name="java.lang.IndexOutOfBoundsException";
                simpleName="IndexOutOfBoundsException";
                serialVersionUID=-7034897190745766939ULL;
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JIndexOutOfBoundsException();
            }
        };

        static JClass* clazz;

        JClass* JIndexOutOfBoundsException::getClazz(){
            if (clazz==NULL){
                clazz=new JIndexOutOfBoundsExceptionClass();
            }
            return clazz;
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(JClass* _class):JRuntimeException(_class){
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException():JRuntimeException(getClazz()){
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(string message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JIndexOutOfBoundsException::~JIndexOutOfBoundsException(){
        }
    }
}
