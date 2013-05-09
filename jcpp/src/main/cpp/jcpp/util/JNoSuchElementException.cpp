#include "JNoSuchElementException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace util{
        class JNoSuchElementExceptionClass : public JClass{
        public:
            JNoSuchElementExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.util.NoSuchElementException";
                name="java.util.NoSuchElementException";
                simpleName="NoSuchElementException";
                serialVersionUID=6769829250639411880ULL;
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

        JNoSuchElementException::JNoSuchElementException(JString message):JRuntimeException(getClazz()){
            this->message=new JString(message);
        }

        JNoSuchElementException::JNoSuchElementException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JNoSuchElementException::~JNoSuchElementException(){
        }
    }
}

