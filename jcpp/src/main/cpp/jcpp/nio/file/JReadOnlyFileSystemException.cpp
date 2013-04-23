#include "JReadOnlyFileSystemException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JReadOnlyFileSystemExceptionClass : public JClass{
                public:
                    JReadOnlyFileSystemExceptionClass(){
                        this->canonicalName="java.nio.file.ReadOnlyFileSystemException";
                        this->name="java.nio.file.ReadOnlyFileSystemException";
                        this->simpleName="ReadOnlyFileSystemException";
                        this->serialVersionUID=-6822409595617487197ULL;
                    }

                    JClass* getSuperclass(){
                        return JUnsupportedOperationException::getClazz();
                    }

                    JObject* newInstance(){
                        return new JReadOnlyFileSystemException();
                    }
            };

            static JClass* clazz;

            JClass* JReadOnlyFileSystemException::getClazz(){
                if (clazz==NULL){
                    clazz=new JReadOnlyFileSystemExceptionClass();
                }
                return clazz;
            }

            JReadOnlyFileSystemException::JReadOnlyFileSystemException():JUnsupportedOperationException(getClazz()){
            }

            JReadOnlyFileSystemException::~JReadOnlyFileSystemException(){
            }
        }
    }
}
