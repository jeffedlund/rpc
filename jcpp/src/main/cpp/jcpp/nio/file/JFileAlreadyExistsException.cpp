#include "JFileAlreadyExistsException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JFileAlreadyExistsExceptionClass : public JClass{
                public:
                    JFileAlreadyExistsExceptionClass(){
                        this->canonicalName="java.nio.file.FileAlreadyExistsException";
                        this->name="java.nio.file.FileAlreadyExistsException";
                        this->simpleName="FileAlreadyExistsException";
                        this->serialVersionUID=7579540934498831181ULL;
                    }

                    JClass* getSuperclass(){
                        return JFileSystemException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JFileAlreadyExistsException();
                    }
            };

            static JClass* clazz;

            JClass* JFileAlreadyExistsException::getClazz(){
                if (clazz==NULL){
                    clazz=new JFileAlreadyExistsExceptionClass();
                }
                return clazz;
            }

            JFileAlreadyExistsException::JFileAlreadyExistsException():JFileSystemException(getClazz()){
            }

            JFileAlreadyExistsException::JFileAlreadyExistsException(JString file):JFileSystemException(getClazz(),file){
            }

            JFileAlreadyExistsException::JFileAlreadyExistsException(JString file,JString other,JString reason):JFileSystemException(getClazz(),file,other,reason){
            }

            JFileAlreadyExistsException::~JFileAlreadyExistsException(){
            }
        }
    }
}

