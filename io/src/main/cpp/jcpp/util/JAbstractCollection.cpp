#include "JAbstractCollection.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"

namespace jcpp{
    namespace util{
        class JAbstractCollectionClass : public JClass{

        public:
          JAbstractCollectionClass(){
              this->canonicalName="java.util.AbstractCollection";
              this->name="java.util.AbstractCollection";
              this->simpleName="AbstractCollection";
              this->serialVersionUID=0;
              addInterface(JCollection::getClazz());
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JAbstractCollection::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractCollectionClass();
            }
            return clazz;
        }

        JAbstractCollection::JAbstractCollection(JClass* _class):JObject(_class){
        }
    }
}
