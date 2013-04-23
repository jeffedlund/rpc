#include "JWatchKey.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchKeyClass : public JClass{
                public:
                    JWatchKeyClass(){
                        this->canonicalName="java.nio.file.WatchKey";
                        this->name="java.nio.file.WatchKey";
                        this->simpleName="WatchKey";
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JWatchKey::getClazz(){
                if (clazz==NULL){
                    clazz=new JWatchKeyClass();
                }
                return clazz;
            }

            JWatchKey::~JWatchKey(){
            }
        }
    }
}
