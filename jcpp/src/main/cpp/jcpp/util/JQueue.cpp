#include "JQueue.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JCollection.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JQueueClass : public JClass{

        public:
          JQueueClass(){
              this->canonicalName="java.util.Queue";
              this->name="java.util.Queue";
              this->simpleName="Queue";
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

        JClass* JQueue::getClazz(){
            if (clazz==NULL){
                clazz=new JQueueClass();
            }
            return clazz;
        }

        JQueue::~JQueue(){
        }
    }
}
