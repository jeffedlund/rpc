#include "JIOError.h"

namespace jcpp{
    namespace io{
        class JIOErrorClass : public JClass{
            public:
                JIOErrorClass(){
                    this->canonicalName="java.io.IOError";
                    this->name="java.io.IOError";
                    this->simpleName="IOError";
                    this->serialVersionUID=67100927991680413ULL;
                }

                JClass* getSuperclass(){
                    return JError::getClazz();
                }

                JObject* newInstance(){
                    return new JIOError();
                }
        };

        static JClass* clazz;

        JClass* JIOError::getClazz(){
            if (clazz==NULL){
                clazz=new JIOErrorClass();
            }
            return clazz;
        }

        JIOError::JIOError():JError(getClazz()){
        }

        JIOError::JIOError(JString message):JError(getClazz()){
            this->message=new JString(message);
        }

        JIOError::JIOError(JThrowable* cause):JError(getClazz()){
            this->cause=cause;
        }

        JIOError::~JIOError(){
        }
    }
}
