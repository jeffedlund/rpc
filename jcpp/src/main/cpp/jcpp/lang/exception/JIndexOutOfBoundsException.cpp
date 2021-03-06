#include "JIndexOutOfBoundsException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JIndexOutOfBoundsExceptionClass : public JClass{
        public:
            JIndexOutOfBoundsExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.IndexOutOfBoundsException";
                name="java.lang.IndexOutOfBoundsException";
                simpleName="IndexOutOfBoundsException";
                serialVersionUID=234122996006267687ULL;
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

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(JString message):JRuntimeException(getClazz()){
            setMessage(new JString(message));
        }

        JIndexOutOfBoundsException::~JIndexOutOfBoundsException(){
        }
    }
}
