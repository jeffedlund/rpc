#include "JNotLinkException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JNotLinkExceptionClass : public JClass{
                public:
                    JNotLinkExceptionClass(){
                        this->canonicalName="java.nio.file.NotLinkException";
                        this->name="java.nio.file.NotLinkException";
                        this->simpleName="NotLinkException";
                        this->serialVersionUID=-388655596416518021ULL;
                    }

                    JClass* getSuperclass(){
                        return JFileSystemException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JNotLinkException();
                    }
            };

            static JClass* clazz;

            JClass* JNotLinkException::getClazz(){
                if (clazz==NULL){
                    clazz=new JNotLinkExceptionClass();
                }
                return clazz;
            }

            JNotLinkException::JNotLinkException():JFileSystemException(getClazz()){
            }

            JNotLinkException::JNotLinkException(JString file):JFileSystemException(getClazz(),file){
            }

            JNotLinkException::JNotLinkException(JString file,JString other,JString reason):JFileSystemException(getClazz(),file,other,reason){
            }

            JNotLinkException::~JNotLinkException(){
            }
       }
    }
}
