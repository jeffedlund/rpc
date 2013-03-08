#include "JInvalidClassException.h"

namespace jcpp{
    namespace io{
        class JInvalidClassExceptionClass : public JClass{
        public:
            JInvalidClassExceptionClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.io.InvalidClassException";
                name="java.io.InvalidClassException";
                simpleName="InvalidClassException";
                serialVersionUID=-4333316296251054416ULL;
            }

            JClass* getSuperclass(){
                return JObjectStreamException::getClazz();
            }

            JObject* newInstance(){
                return new JInvalidClassException();
            }
        };

        static JClass* clazz;

        JClass* JInvalidClassException::getClazz(){
            if (clazz==NULL){
                clazz=new JInvalidClassExceptionClass();
            }
            return clazz;
        }

        JInvalidClassException::JInvalidClassException():JObjectStreamException(getClazz()){
        }

        JInvalidClassException::JInvalidClassException(string message) : JObjectStreamException(getClazz()){
            this->message=new JString(message);
        }

        JInvalidClassException::~JInvalidClassException(){
        }
    }
}
