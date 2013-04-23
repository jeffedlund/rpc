#include "JDirectoryIteratorException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JDirectoryIteratorExceptionClass : public JClass{
            public:
                JDirectoryIteratorExceptionClass(){
                    this->canonicalName="java.nio.file.DirectoryIteratorException";
                    this->name="java.nio.file.DirectoryIteratorException";
                    this->simpleName="DirectoryIteratorException";
                    this->serialVersionUID=-6012699886086212874ULL;
                }

                JClass* getSuperclass(){
                    return JConcurrentModificationException::getClazz();
                }

                JObject* newInstance(){
                    return new JDirectoryIteratorException();
                }
            };

            static JClass* clazz;

            JClass* JDirectoryIteratorException::getClazz(){
                if (clazz==NULL){
                    clazz=new JDirectoryIteratorExceptionClass();
                }
                return clazz;
            }

            JDirectoryIteratorException::JDirectoryIteratorException():JConcurrentModificationException(getClazz()){
            }

            JDirectoryIteratorException::JDirectoryIteratorException(JIOException* cause):JConcurrentModificationException(getClazz()){
                this->cause=cause;
            }

            JDirectoryIteratorException::~JDirectoryIteratorException(){
            }
        }
    }
}
