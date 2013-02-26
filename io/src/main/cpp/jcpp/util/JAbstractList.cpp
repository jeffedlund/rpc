#include "JAbstractList.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"

namespace jcpp{
    namespace util{
        class JAbstractListClass : public JClass{

        public:
          JAbstractListClass(){
              this->canonicalName="java.util.AbstractList";
              this->name="java.util.AbstractList";
              this->simpleName="AbstractList";
              this->serialVersionUID=0;
              addInterface(JList::getClazz());
          }

          JClass* getSuperclass(){
              return JAbstractCollection::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JAbstractList::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractListClass();
            }
            return clazz;
        }

        JAbstractList::JAbstractList(JClass* _class):JAbstractCollection(_class){
        }

        JAbstractList::~JAbstractList(){
        }
    }
}
