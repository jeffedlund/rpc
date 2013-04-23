#include "JClosedWatchServiceException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JClosedWatchServiceExceptionClass : public JClass{
                public:
                    JClosedWatchServiceExceptionClass(){
                        this->canonicalName="java.nio.file.ClosedWatchServiceException";
                        this->name="java.nio.file.ClosedWatchServiceException";
                        this->simpleName="ClosedWatchServiceException";
                        this->serialVersionUID=1853336266231677732ULL;
                    }

                    JClass* getSuperclass(){
                        return JIllegalStateException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JClosedWatchServiceException();
                    }
            };

            static JClass* clazz;

            JClass* JClosedWatchServiceException::getClazz(){
                if (clazz==NULL){
                    clazz=new JClosedWatchServiceExceptionClass();
                }
                return clazz;
            }

            JClosedWatchServiceException::JClosedWatchServiceException():JIllegalStateException(getClazz()){
            }

            JClosedWatchServiceException::~JClosedWatchServiceException(){
            }
        }
    }
}
