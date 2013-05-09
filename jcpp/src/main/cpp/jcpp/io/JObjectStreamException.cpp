#include "JObjectStreamException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JObjectStreamExceptionClass : public JClass{
        public:
            JObjectStreamExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.ObjectStreamException";
                name="java.io.ObjectStreamException";
                simpleName="ObjectStreamException";
                serialVersionUID=7260898174833392607ULL;
            }

            JClass* getSuperclass(){
                return JIOException::getClazz();
            }

            JObject* newInstance(){
                return new JObjectStreamException();
            }
        };

        static JClass* clazz;

        JClass* JObjectStreamException::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectStreamExceptionClass();
            }
            return clazz;
        }

        JObjectStreamException::JObjectStreamException(JClass* _class):JIOException(_class){
        }

        JObjectStreamException::JObjectStreamException():JIOException(getClazz()){
        }

        JObjectStreamException::JObjectStreamException(JString message) : JIOException(getClazz()){
            this->message=new JString(message);
        }

        JObjectStreamException::~JObjectStreamException(){
        }
    }
}
