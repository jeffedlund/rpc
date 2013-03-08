#include "JError.h"
#include "JClass.h"

namespace jcpp{
    namespace lang{
        class JErrorClass : public JClass{
        public :
            JErrorClass(){
                canonicalName="java.lang.Error";
                name="java.lang.Error";
                simpleName="Error";
                serialVersionUID=4980196508277280342ULL;
            }

            JClass* getSuperclass(){
                return JThrowable::getClazz();
            }

            JObject* newInstance(){
                return new JError();
            }
        };

        static JClass* clazz;

        JClass* JError::getClazz(){
            if (clazz==NULL){
                clazz=new JErrorClass();
            }
            return clazz;
        }

        JError::JError():JThrowable(getClazz()){
        }

        JError::JError(JClass* _class):JThrowable(_class){
        }

        JError::JError(string message):JThrowable(getClazz()){
            this->message = new JString(message);
        }

        JError::JError(string message, JThrowable *cause):JThrowable(getClazz()){
            this->message = new JString(message);
            this->cause = cause;
        }

        JError::~JError(){
        }
    }
}

