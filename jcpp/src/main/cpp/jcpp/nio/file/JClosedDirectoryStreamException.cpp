#include "JClosedDirectoryStreamException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JClosedDirectoryStreamExceptionClass : public JClass{
            public:
                JClosedDirectoryStreamExceptionClass(){
                    this->canonicalName="java.nio.file.ClosedDirectoryStreamException";
                    this->name="java.nio.file.ClosedDirectoryStreamException";
                    this->simpleName="ClosedDirectoryStreamException";
                    this->serialVersionUID=4228386650900895400ULL;
                }

                JClass* getSuperclass(){
                    return JIllegalStateException::getClazz();
                }

                JObject* newInstance(){
                    return new JClosedDirectoryStreamException();
                }
            };

            static JClass* clazz;

            JClass* JClosedDirectoryStreamException::getClazz(){
                if (clazz==NULL){
                    clazz=new JClosedDirectoryStreamExceptionClass();
                }
                return clazz;
            }

            JClosedDirectoryStreamException::JClosedDirectoryStreamException():JIllegalStateException(getClazz()){
            }

            JClosedDirectoryStreamException::~JClosedDirectoryStreamException(){
            }
        }
    }
}
