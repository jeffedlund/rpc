#include "JCloneable.h"
#include "JInstantiationException.h"

namespace jcpp{
    namespace lang{
        class JCloneableClass : public JClass{
          public:
            JCloneableClass():JClass(){
                this->canonicalName="java.lang.Cloneable";
                this->name="java.lang.Cloneable";
                this->simpleName="Cloneable";
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
            }
        };

        static JClass* clazz;

        JClass* JCloneable::getClazz(){
            if (clazz==NULL){
                clazz=new JCloneableClass();
            }
            return clazz;
        }

        JCloneable::~JCloneable(){
        }
    }
}
