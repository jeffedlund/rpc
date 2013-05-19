#include "JFilter.h"
#include "JClass.h"

namespace jcpp{
    namespace util{
        namespace logging{
            class JFilterClass : public JClass{
                public:
                    JFilterClass(){
                        this->canonicalName="java.util.logging.Filter";
                        this->name="java.util.logging.Filter";
                        this->simpleName="Filter";
                    }

                    JClass* getSuperclass(){
                        return JInterface::getClazz();
                    }
            };

            static JClass* clazz;

            JClass* JFilter::getClazz(){
                if (clazz==NULL){
                    clazz=new JFilterClass();
                }
                return clazz;
            }

            JFilter::~JFilter(){
            }
        }
    }
}
