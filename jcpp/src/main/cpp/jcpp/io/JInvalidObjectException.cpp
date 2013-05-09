#include "JInvalidObjectException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JInvalidObjectExceptionClass : public JClass{
        public:
            JInvalidObjectExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.InvalidObjectException";
                name="java.io.InvalidObjectException";
                simpleName="InvalidObjectException";
                serialVersionUID=3233174318281839583ULL;
            }

            JClass* getSuperclass(){
                return JObjectStreamException::getClazz();
            }

            JObject* newInstance(){
                return new JInvalidObjectException();
            }
        };

        static JClass* clazz;

        JClass* JInvalidObjectException::getClazz(){
            if (clazz==NULL){
                clazz=new JInvalidObjectExceptionClass();
            }
            return clazz;
        }

        JInvalidObjectException::JInvalidObjectException():JObjectStreamException(getClazz()){
        }

        JInvalidObjectException::JInvalidObjectException(JString message) : JObjectStreamException(getClazz()){
            this->message=new JString(message);
        }

        JInvalidObjectException::~JInvalidObjectException(){
        }
    }
}

