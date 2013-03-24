#include "JDictionary.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JDictionaryClass : public JClass{

        public:
          JDictionaryClass(){
              this->canonicalName="java.util.Dictionary";
              this->name="java.util.Dictionary";
              this->simpleName="Dictionary";
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          JObject* newInstance(){
              throw new JInstantiationException("cannot instantiate object of class "+getName());
          }
        };

        static JClass* clazz;

        JClass* JDictionary::getClazz(){
            if (clazz==NULL){
                clazz=new JDictionaryClass();
            }
            return clazz;
        }

        JDictionary::JDictionary(JClass *_class):JObject(_class){
        }

        JDictionary::~JDictionary(){
        }
    }
}



