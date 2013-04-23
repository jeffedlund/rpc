#include "JWatchable.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JWatchableClass : public JClass{
                public:
                    JWatchableClass(){
                        this->canonicalName="java.nio.file.Watchable";
                        this->name="java.nio.file.Watchable";
                        this->simpleName="Watchable";
                        this->bIsInterface=true;
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JWatchable::getClazz(){
                if (clazz==NULL){
                    clazz=new JWatchableClass();
                }
                return clazz;
            }

            JWatchable::~JWatchable(){
            }
        }
    }
}
