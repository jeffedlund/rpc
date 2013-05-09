#include "JProviderNotFoundException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JProviderNotFoundExceptionClass : public JClass{
                public:
                    JProviderNotFoundExceptionClass(){
                        this->canonicalName="java.nio.file.ProviderNotFoundException";
                        this->name="java.nio.file.ProviderNotFoundException";
                        this->simpleName="ProviderNotFoundException";
                        this->serialVersionUID=-1880012509822920354ULL;
                    }

                    JClass* getSuperclass(){
                        return JRuntimeException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JProviderNotFoundException();
                    }
            };

            static JClass* clazz;

            JClass* JProviderNotFoundException::getClazz(){
                if (clazz==NULL){
                    clazz=new JProviderNotFoundExceptionClass();
                }
                return clazz;
            }

            JProviderNotFoundException::JProviderNotFoundException():JRuntimeException(getClazz()){
            }

            JProviderNotFoundException::JProviderNotFoundException(JString msg):JRuntimeException(getClazz()){
                this->message=new JString(msg);
            }

            JProviderNotFoundException::~JProviderNotFoundException(){
            }
        }
    }
}
