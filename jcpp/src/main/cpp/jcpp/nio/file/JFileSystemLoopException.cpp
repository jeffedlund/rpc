#include "JFileSystemLoopException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileSystemLoopExceptionClass : public JClass{
                public:
                    JFileSystemLoopExceptionClass(){
                        this->canonicalName="java.nio.file.FileSystemLoopException";
                        this->name="java.nio.file.FileSystemLoopException";
                        this->simpleName="FileSystemLoopException";
                        this->serialVersionUID=4843039591949217617ULL;
                    }

                    JClass* getSuperclass(){
                        return JFileSystemException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JFileSystemLoopException();
                    }
            };

            static JClass* clazz;

            JClass* JFileSystemLoopException::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileSystemLoopExceptionClass();
                }
                return clazz;
            }

            JFileSystemLoopException::JFileSystemLoopException():JFileSystemException(getClazz()){
            }

            JFileSystemLoopException::JFileSystemLoopException(string file):JFileSystemException(getClazz(),file){
            }

            JFileSystemLoopException::~JFileSystemLoopException(){
            }
        }
    }
}
