#include "JArrayIndexOutOfBoundsException.h"

namespace jcpp{
    namespace lang{
        class JArrayIndexOutOfBoundsExceptionClass : public JClass{
        public:
            JArrayIndexOutOfBoundsExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.ArrayIndexOutOfBoundsException";
                name="java.lang.ArrayIndexOutOfBoundsException";
                simpleName="ArrayIndexOutOfBoundsException";
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JArrayIndexOutOfBoundsException();
            }
        };

        static JClass* clazz;

        JClass* JArrayIndexOutOfBoundsException::getClazz(){
            if (clazz==NULL){
                clazz=new JArrayIndexOutOfBoundsExceptionClass();
            }
            return clazz;
        }

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException():JIndexOutOfBoundsException(getClazz()){
        }

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException(string message):JIndexOutOfBoundsException(getClazz()){
            this->message=new JString(message);
        }

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException(JString* message):JIndexOutOfBoundsException(getClazz()){
            this->message=message;
        }

        JArrayIndexOutOfBoundsException::~JArrayIndexOutOfBoundsException(){
        }
    }
}
