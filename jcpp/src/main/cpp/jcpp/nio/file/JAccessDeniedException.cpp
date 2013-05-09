#include "JAccessDeniedException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JAccessDeniedExceptionClass : public JClass{
                public:
                    JAccessDeniedExceptionClass(){
                        this->canonicalName="java.nio.file.AccessDeniedException";
                        this->name="java.nio.file.AccessDeniedException";
                        this->simpleName="AccessDeniedException";
                        this->serialVersionUID=4943049599949219617ULL;
                    }

                    JClass* getSuperclass(){
                        return JFileSystemException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JAccessDeniedException();
                    }
            };

            static JClass* clazz;

            JClass* JAccessDeniedException::getClazz(){
                if (clazz==NULL){
                    clazz=new JAccessDeniedExceptionClass();
                }
                return clazz;
            }

            JAccessDeniedException::JAccessDeniedException():JFileSystemException(getClazz()){
            }

            JAccessDeniedException::JAccessDeniedException(JString file):JFileSystemException(getClazz(),file){
            }

            JAccessDeniedException::JAccessDeniedException(JString file,JString other,JString reason):JFileSystemException(getClazz(),file,other,reason){
            }

            JAccessDeniedException::~JAccessDeniedException(){
            }
        }
    }
}
