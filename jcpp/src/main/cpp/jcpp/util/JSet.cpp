#include "JSet.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JCollection.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JSetClass : public JClass{

        public:
          JSetClass(){
              this->canonicalName="java.util.Set";
              this->name="java.util.Set";
              this->simpleName="Set";
              this->serialVersionUID=0;
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JCollection::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JSet::getClazz(){
            if (clazz==NULL){
                clazz=new JSetClass();
            }
            return clazz;
        }

        JSet::~JSet(){
        }
    }
}
