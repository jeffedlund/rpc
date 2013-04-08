#include "JNoSuchMethodException.h"

namespace jcpp{
    namespace lang{
        class JNoSuchMethodExceptionClass : public JClass{
        public:
            JNoSuchMethodExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.NoSuchMethodException";
                name="java.lang.NoSuchMethodException";
                simpleName="NoSuchMethodException";
                serialVersionUID=5034388446362600923ULL;
            }

            JClass* getSuperclass(){
                return JException::getClazz();
            }

            JObject* newInstance(){
                return new JNoSuchMethodException();
            }
        };

        static JClass* clazz;

        JClass* JNoSuchMethodException::getClazz(){
            if (clazz==NULL){
                clazz=new JNoSuchMethodExceptionClass();
            }
            return clazz;
        }

        JNoSuchMethodException::JNoSuchMethodException():JException(getClazz()){
        }

        JNoSuchMethodException::JNoSuchMethodException(string message):JException(getClazz()){
            this->message=new JString(message);
        }

        JNoSuchMethodException::~JNoSuchMethodException(){
        }
    }
}

