#include "JNoSuchFileException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JNoSuchFileExceptionClass : public JClass{
                public:
                    JNoSuchFileExceptionClass(){
                        this->canonicalName="java.nio.file.NoSuchFileException";
                        this->name="java.nio.file.NoSuchFileException";
                        this->simpleName="NoSuchFileException";
                        this->serialVersionUID=-1390291775875351931ULL;
                    }

                    JClass* getSuperclass(){
                        return JFileSystemException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JNoSuchFileException();
                    }
            };

            static JClass* clazz;

            JClass* JNoSuchFileException::getClazz(){
                if (clazz==NULL){
                    clazz=new JNoSuchFileExceptionClass();
                }
                return clazz;
            }

            JNoSuchFileException::JNoSuchFileException():JFileSystemException(getClazz()){
            }

            JNoSuchFileException::JNoSuchFileException(JString file):JFileSystemException(getClazz(),file){
            }

            JNoSuchFileException::JNoSuchFileException(JString file,JString other,JString reason):JFileSystemException(getClazz(),file,other,reason){
            }

            JNoSuchFileException::~JNoSuchFileException(){
            }
        }
    }
}
