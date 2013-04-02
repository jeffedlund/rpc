#include "JCollection.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JCollectionClass : public JClass{

        public:
          JCollectionClass(){
              this->canonicalName="java.util.Collection";
              this->name="java.util.Collection";
              this->simpleName="Collection";
              this->serialVersionUID=0;
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JInterface::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JCollection::getClazz(){
            if (clazz==NULL){
                clazz=new JCollectionClass();
            }
            return clazz;
        }

        JCollection::~JCollection(){
        }
    }
}
