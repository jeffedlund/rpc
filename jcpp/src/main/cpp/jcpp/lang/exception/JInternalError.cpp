#include "JInternalError.h"
#include "JClass.h"
#include "JClassLoader.h"

namespace jcpp{
    namespace lang{
        class JInternalErrorClass : public JClass{
        public:
            JInternalErrorClass():JClass(JClassLoader::getBootClassLoader()){
                canonicalName="java.lang.InternalError";
                name="java.lang.InternalError";
                simpleName="InternalError";
                serialVersionUID=-9062593416125562365ULL;
            }

            JClass* getSuperclass(){
                return JVirtualMachineError::getClazz();
            }

            JObject* newInstance(){
                return new JInternalError();
            }
        };

        static JClass* clazz;

        JClass* JInternalError::getClazz(){
            if (clazz==NULL){
                clazz=new JInternalErrorClass();
            }
            return clazz;
        }

        JInternalError::JInternalError():JVirtualMachineError(getClazz()){
        }

        JInternalError::JInternalError(JClass* _class):JVirtualMachineError(_class){
        }

        JInternalError::JInternalError(JString message):JVirtualMachineError(getClazz()){
            this->message = new JString(message);
        }

        JInternalError::JInternalError(JString message, JThrowable *cause):JVirtualMachineError(getClazz()){
            this->message = new JString(message);
            this->cause = cause;
        }

        JInternalError::~JInternalError(){
        }
    }
}

