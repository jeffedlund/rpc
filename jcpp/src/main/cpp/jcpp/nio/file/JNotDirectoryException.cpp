#include "JNotDirectoryException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JNotDirectoryExceptionClass : public JClass{
                public:
                    JNotDirectoryExceptionClass(){
                        this->canonicalName="java.nio.file.NotDirectoryException";
                        this->name="java.nio.file.NotDirectoryException";
                        this->simpleName="NotDirectoryException";
                        this->serialVersionUID=-9011457427178200199ULL;
                    }

                    JClass* getSuperclass(){
                        return JFileSystemException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JNotDirectoryException();
                    }
            };

            static JClass* clazz;

            JClass* JNotDirectoryException::getClazz(){
                if (clazz==NULL){
                    clazz=new JNotDirectoryExceptionClass();
                }
                return clazz;
            }

            JNotDirectoryException::JNotDirectoryException():JFileSystemException(getClazz()){
            }

            JNotDirectoryException::JNotDirectoryException(JString file):JFileSystemException(getClazz(),file){
            }

            JNotDirectoryException::~JNotDirectoryException(){
            }
        }
    }
}
