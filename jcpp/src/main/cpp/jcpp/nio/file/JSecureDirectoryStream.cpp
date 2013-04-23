#include "JSecureDirectoryStream.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
        class JSecureDirectoryStreamClass : public JClass{
            public:
                JSecureDirectoryStreamClass(){
                    this->canonicalName="java.nio.file.SecureDirectoryStream";
                    this->name="java.nio.file.SecureDirectoryStream";
                    this->simpleName="SecureDirectoryStream";
                    this->bIsInterface=true;
                    addInterface(JDirectoryStream::getClazz());
                }

                JClass* getSuperclass(){
                    return JDirectoryStream::getClazz();
                }
            };

            static JClass* clazz;

            JClass* JSecureDirectoryStream::getClazz(){
                if (clazz==NULL){
                    clazz=new JSecureDirectoryStreamClass();
                }
                return clazz;
            }

            JSecureDirectoryStream::~JSecureDirectoryStream(){
            }
        }
    }
}
