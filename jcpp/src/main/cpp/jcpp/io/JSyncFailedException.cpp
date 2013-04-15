#include "JSyncFailedException.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JSyncFailedExceptionClass : public JClass{
            public:
                JSyncFailedExceptionClass(){
                    this->canonicalName="java.io.SyncFailedException";
                    this->name="java.io.SyncFailedException";
                    this->simpleName="SyncFailedException";
                    this->serialVersionUID=-2353342684412443330ULL;
                }

                JClass* getSuperclass(){
                    return JIOException::getClazz();
                }

                JObject* newInstance(){
                    return new JSyncFailedException();
                }
        };

        static JClass* clazz;

        JClass* JSyncFailedException::getClazz(){
            if (clazz==NULL){
                clazz=new JSyncFailedExceptionClass();
            }
            return clazz;
        }

        JSyncFailedException::JSyncFailedException():JIOException(getClazz()){
        }

        JSyncFailedException::~JSyncFailedException(){
        }
    }
}
