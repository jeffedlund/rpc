#include "JPathMatcher.h"
#include "JClass.h"

namespace jcpp{
    namespace nio{
        namespace file{
            class JPathMatcherClass : public JClass{
                public:
                    JPathMatcherClass(){
                        this->canonicalName="java.nio.file.PathMatcher";
                        this->name="java.nio.file.PathMatcher";
                        this->simpleName="PathMatcher";
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JPathMatcher::getClazz(){
                if (clazz==NULL){
                    clazz=new JPathMatcherClass();
                }
                return clazz;
            }

            JPathMatcher::~JPathMatcher(){
            }
        }
    }
}
