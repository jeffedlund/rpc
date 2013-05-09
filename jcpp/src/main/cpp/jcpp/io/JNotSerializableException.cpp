#include "JNotSerializableException.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace io{
        class JNotSerializableExceptionClass : public JClass{
        public:
            JNotSerializableExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.NotSerializableException";
                name="java.io.NotSerializableException";
                simpleName="NotSerializableException";
                serialVersionUID=2906642554793891381ULL;
            }

            JClass* getSuperclass(){
                return JObjectStreamException::getClazz();
            }

            JObject* newInstance(){
                return new JNotSerializableException();
            }
        };

        static JClass* clazz;

        JClass* JNotSerializableException::getClazz(){
            if (clazz==NULL){
                clazz=new JNotSerializableExceptionClass();
            }
            return clazz;
        }

        JNotSerializableException::JNotSerializableException(JClass* _class):JObjectStreamException(_class){
        }

        JNotSerializableException::JNotSerializableException():JObjectStreamException(getClazz()){
        }

        JNotSerializableException::JNotSerializableException(JString message) : JObjectStreamException(getClazz()){
            this->message=new JString(message);
        }

        JNotSerializableException::~JNotSerializableException(){
        }
    }
}
