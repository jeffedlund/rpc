#include "JAtomicMoveNotSupportedException.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JAtomicMoveNotSupportedExceptionClass : public JClass{
            public:
                JAtomicMoveNotSupportedExceptionClass(){
                    this->canonicalName="java.nio.file.AtomicMoveNotSupportedException";
                    this->name="java.nio.file.AtomicMoveNotSupportedException";
                    this->simpleName="AtomicMoveNotSupportedException";
                    this->serialVersionUID=5402760225333135579ULL;
                }

                JClass* getSuperclass(){
                    return JFileSystemException::getClazz();
                }

                JObject* newInstance(){
                    return new JAtomicMoveNotSupportedException();
                }
            };

            static JClass* clazz;

            JClass* JAtomicMoveNotSupportedException::getClazz(){
                if (clazz==NULL){
                    clazz=new JAtomicMoveNotSupportedExceptionClass();
                }
                return clazz;
            }

            JAtomicMoveNotSupportedException::JAtomicMoveNotSupportedException():JFileSystemException(getClazz()){
            }

            JAtomicMoveNotSupportedException::JAtomicMoveNotSupportedException(JString source,JString target,JString reason):JFileSystemException(getClazz(),source,target,reason){
            }

            JAtomicMoveNotSupportedException::~JAtomicMoveNotSupportedException(){
            }
        }
    }
}
