#include "JFileSystemNotFoundException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemNotFoundExceptionClass : public JClass{
                public:
                    JFileSystemNotFoundExceptionClass(){
                        this->canonicalName="java.nio.file.FileSystemNotFoundException";
                        this->name="java.nio.file.FileSystemNotFoundException";
                        this->simpleName="FileSystemNotFoundException";
                        this->serialVersionUID=7999581764446402397ULL;
                    }

                    JClass* getSuperclass(){
                        return JRuntimeException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JFileSystemNotFoundException();
                    }
            };

            static JClass* clazz;

            JClass* JFileSystemNotFoundException::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileSystemNotFoundExceptionClass();
                }
                return clazz;
            }

            JFileSystemNotFoundException::JFileSystemNotFoundException():JRuntimeException(getClazz()){
            }

            JFileSystemNotFoundException::JFileSystemNotFoundException(string msg):JRuntimeException(getClazz()){
                this->message=new JString(msg);
            }

            JFileSystemNotFoundException::~JFileSystemNotFoundException(){
            }
        }
    }
}
