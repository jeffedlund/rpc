#include "JFileSystemAlreadyExistsException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemAlreadyExistsExceptionClass : public JClass{
                public:
                    JFileSystemAlreadyExistsExceptionClass(){
                        this->canonicalName="java.nio.file.FileSystemAlreadyExistsException";
                        this->name="java.nio.file.FileSystemAlreadyExistsException";
                        this->simpleName="FileSystemAlreadyExistsException";
                        this->serialVersionUID=-5438419127181131148ULL;
                    }

                    JClass* getSuperclass(){
                        return JRuntimeException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JFileSystemAlreadyExistsException();
                    }
            };

            static JClass* clazz;

            JClass* JFileSystemAlreadyExistsException::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileSystemAlreadyExistsExceptionClass();
                }
                return clazz;
            }

            JFileSystemAlreadyExistsException::JFileSystemAlreadyExistsException():JRuntimeException(getClazz()){
            }

            JFileSystemAlreadyExistsException::JFileSystemAlreadyExistsException(JString msg):JRuntimeException(getClazz()){
                this->message=new JString(msg);
            }

            JFileSystemAlreadyExistsException::~JFileSystemAlreadyExistsException(){
            }
        }
    }
}
