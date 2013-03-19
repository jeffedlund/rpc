#include "JNoSuchElementException.h"

namespace jcpp{
    namespace util{
        class JNoSuchElementExceptionClass : public JClass{
        public:
            JNoSuchElementExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.util.NoSuchElementException";
                name="java.util.NoSuchElementException";
                simpleName="NoSuchElementException";
            }

            JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }

            JObject* newInstance(){
                return new JNoSuchElementException();
            }
        };

        static JClass* clazz;

        JClass* JNoSuchElementException::getClazz(){
            if (clazz==NULL){
                clazz=new JNoSuchElementExceptionClass();
            }
            return clazz;
        }

        JNoSuchElementException::JNoSuchElementException():JRuntimeException(getClazz()){
        }

        JNoSuchElementException::JNoSuchElementException(string message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JNoSuchElementException::JNoSuchElementException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JNoSuchElementException::~JNoSuchElementException(){
        }
    }
}

