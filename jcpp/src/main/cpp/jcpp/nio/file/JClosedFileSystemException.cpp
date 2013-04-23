#include "JClosedFileSystemException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JClosedFileSystemExceptionClass : public JClass{
                public:
                    JClosedFileSystemExceptionClass(){
                        this->canonicalName="java.nio.file.ClosedFileSystemException";
                        this->name="java.nio.file.ClosedFileSystemException";
                        this->simpleName="ClosedFileSystemException";
                        this->serialVersionUID=-8158336077256193488ULL;
                    }

                    JClass* getSuperclass(){
                        return JIllegalStateException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JClosedFileSystemException();
                    }
            };

            static JClass* clazz;

            JClass* JClosedFileSystemException::getClazz(){
                if (clazz==NULL){
                    clazz=new JClosedFileSystemExceptionClass();
                }
                return clazz;
            }

            JClosedFileSystemException::JClosedFileSystemException():JIllegalStateException(getClazz()){
            }

            JClosedFileSystemException::~JClosedFileSystemException(){
            }
        }
    }
}
