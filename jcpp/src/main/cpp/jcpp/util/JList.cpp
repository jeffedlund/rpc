#include "JList.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include "JCollection.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JListClass : public JClass{

        public:
          JListClass(){
              this->canonicalName="java.util.List";
              this->name="java.util.List";
              this->simpleName="List";
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JCollection::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JList::getClazz(){
            if (clazz==NULL){
                clazz=new JListClass();
            }
            return clazz;
        }

        JList::~JList(){
        }
    }
}
