#include "JPath.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JPathClass : public JClass{
                public:
                    JPathClass(){
                        this->canonicalName="java.nio.file.Path";
                        this->name="java.nio.file.Path";
                        this->simpleName="Path";
                        addInterface(JComparable::getClazz());
                        addInterface(JIterable::getClazz());
                        addInterface(JWatchable::getClazz());
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JPath::getClazz(){
                if (clazz==NULL){
                    clazz=new JPathClass();
                }
                return clazz;
            }

            JPath::~JPath(){
            }
        }
    }
}
