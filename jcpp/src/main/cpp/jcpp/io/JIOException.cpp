#include "JIOException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JIOExceptionClass : public JClass{
        public:
            JIOExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.IOException";
                name="java.io.IOException";
                simpleName="IOException";
                serialVersionUID=7818375828146090155ULL;
            }

            JClass* getSuperclass(){
                return JException::getClazz();
            }

            JObject* newInstance(){
                return new JIOException();
            }
        };

        static JClass* clazz;

        JClass* JIOException::getClazz(){
            if (clazz==NULL){
                clazz=new JIOExceptionClass();
            }
            return clazz;
        }

        JIOException::JIOException():JException(getClazz()){
        }

        JIOException::JIOException(JClass* _class):JException(_class){
        }

        JIOException::JIOException(JString message) : JException(getClazz()){
            this->message=new JString(message);
        }

        JIOException::~JIOException(){
        }
    }
}
