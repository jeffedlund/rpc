#include "JMap.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        class JMapClass : public JClass{
        public:
          JMapClass(){
              this->canonicalName="java.util.Map";
              this->name="java.util.Map";
              this->simpleName="Map";
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JInterface::getClazz();
          }

          virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JMap::getClazz(){
            if (clazz==NULL){
                clazz=new JMapClass();
            }
            return clazz;
        }

        class JEntryMapClass : public JClass{
        public:
          JEntryMapClass(){
              this->canonicalName="java.util.Map$Entry";
              this->name="java.util.Map$Entry";
              this->simpleName="Map$Entry";
              this->bIsInterface=true;
          }

          JClass* getSuperclass(){
              return JInterface::getClazz();
          }

          virtual JClass* getDeclaringClass(){
              return JMap::getClazz();
          }
        };

        static JClass* entryClazz;

        JClass* JMap::JEntry::getClazz(){
            if (entryClazz==NULL){
                entryClazz=new JEntryMapClass();
            }
            return entryClazz;
        }

        JMap::JEntry::~JEntry(){
        }

        void JMapClass::fillDeclaredClasses(){
            addDeclaredClass(JMap::JEntry::getClazz());
        }

        JMap::~JMap(){
        }
    }
}
