#include "JDirectoryNotEmptyException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JDirectoryNotEmptyExceptionClass : public JClass{
            public:
                JDirectoryNotEmptyExceptionClass(){
                    this->canonicalName="java.nio.file.DirectoryNotEmptyException";
                    this->name="java.nio.file.DirectoryNotEmptyException";
                    this->simpleName="DirectoryNotEmptyException";
                    this->serialVersionUID=3056667871802779003ULL;
                }

                JClass* getSuperclass(){
                    return JFileSystemException::getClazz();
                }

                JObject* newInstance(){
                    return new JDirectoryNotEmptyException();
                }
            };

            static JClass* clazz;

            JClass* JDirectoryNotEmptyException::getClazz(){
                if (clazz==NULL){
                    clazz=new JDirectoryNotEmptyExceptionClass();
                }
                return clazz;
            }

            JDirectoryNotEmptyException::JDirectoryNotEmptyException():JFileSystemException(getClazz()){
            }

            JDirectoryNotEmptyException::JDirectoryNotEmptyException(JString dir):JFileSystemException(getClazz(),dir){
            }

            JDirectoryNotEmptyException::~JDirectoryNotEmptyException(){
            }
        }
    }
}
