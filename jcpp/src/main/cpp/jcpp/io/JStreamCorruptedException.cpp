#include "JStreamCorruptedException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JStreamCorruptedExceptionClass : public JClass{
        public:
            JStreamCorruptedExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.StreamCorruptedException";
                name="java.io.StreamCorruptedException";
                simpleName="StreamCorruptedException";
                serialVersionUID=8983558202217591746ULL;
            }

            JClass* getSuperclass(){
                return JObjectStreamException::getClazz();
            }

            JObject* newInstance(){
                return new JStreamCorruptedException();
            }
        };

        static JClass* clazz;

        JClass* JStreamCorruptedException::getClazz(){
            if (clazz==NULL){
                clazz=new JStreamCorruptedExceptionClass();
            }
            return clazz;
        }

        JStreamCorruptedException::JStreamCorruptedException(JClass* _class):JObjectStreamException(_class){
        }

        JStreamCorruptedException::JStreamCorruptedException():JObjectStreamException(getClazz()){
        }

        JStreamCorruptedException::JStreamCorruptedException(JString message) : JObjectStreamException(getClazz()){
            this->message=new JString(message);
        }

        JStreamCorruptedException::~JStreamCorruptedException(){
        }
    }
}
