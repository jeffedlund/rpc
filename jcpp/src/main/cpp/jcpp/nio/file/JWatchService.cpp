#include "JWatchService.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchServiceClass : public JClass{
                public:
                    JWatchServiceClass(){
                        this->canonicalName="java.nio.file.WatchService";
                        this->name="java.nio.file.WatchService";
                        this->simpleName="WatchService";
                        addInterface(JCloseable::getClazz());
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JWatchService::getClazz(){
                if (clazz==NULL){
                    clazz=new JWatchServiceClass();
                }
                return clazz;
            }

            JWatchService::~JWatchService(){
            }
        }
    }
}
