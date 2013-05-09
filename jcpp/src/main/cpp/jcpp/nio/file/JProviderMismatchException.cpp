#include "JProviderMismatchException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JProviderMismatchExceptionClass : public JClass{
                public:
                    JProviderMismatchExceptionClass(){
                        this->canonicalName="java.nio.file.ProviderMismatchException";
                        this->name="java.nio.file.ProviderMismatchException";
                        this->simpleName="ProviderMismatchException";
                        this->serialVersionUID=4990847485741612530ULL;
                    }

                    JClass* getSuperclass(){
                        return JIllegalArgumentException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JProviderMismatchException();
                    }
            };

            static JClass* clazz;

            JClass* JProviderMismatchException::getClazz(){
                if (clazz==NULL){
                    clazz=new JProviderMismatchExceptionClass();
                }
                return clazz;
            }

            JProviderMismatchException::JProviderMismatchException():JIllegalArgumentException(getClazz()){
            }

            JProviderMismatchException::JProviderMismatchException(JString msg):JIllegalArgumentException(getClazz()){
                this->message=new JString(msg);
            }

            JProviderMismatchException::~JProviderMismatchException(){
            }
        }
    }
}
