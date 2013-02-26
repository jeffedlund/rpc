#include "JClassNotFoundException.h"

namespace jcpp{
    namespace lang{
        class JClassNotFoundExceptionClass : public JClass{
        public:
            JClassNotFoundExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.ClassNotFoundException";
                name="java.lang.ClassNotFoundException";
                simpleName="ClassNotFoundException";
                serialVersionUID=-9176873029745254542ULL;
            }

            JClass* getSuperclass(){
                return JException::getClazz();
            }

            JObject* newInstance(){
                return new JClassNotFoundException();
            }
        };

        static JClass* clazz;

        JClass* JClassNotFoundException::getClazz(){
            if (clazz==NULL){
                clazz=new JClassNotFoundExceptionClass();
            }
            return clazz;
        }

        JClassNotFoundException::JClassNotFoundException():JException(getClazz()){
        }

        JClassNotFoundException::JClassNotFoundException(string message):JException(getClazz()){
            this->message=new JString(message);
        }

        JClassNotFoundException::~JClassNotFoundException(){
        }
    }
}
