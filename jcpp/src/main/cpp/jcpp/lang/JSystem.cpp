#include "JSystem.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <QDateTime>
#include "Object.h"

namespace jcpp{
    namespace lang{
        class JSystemClass : public JClass{
        public:
          JSystemClass(){
              this->canonicalName="java.lang.System";
              this->name="java.lang.System";
              this->simpleName="System";
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JSystem::getClazz(){
            if (clazz==NULL){
                clazz=new JSystemClass();
            }
            return clazz;
        }

        jlong JSystem::currentTimeMillis(){
            return QDateTime::currentMSecsSinceEpoch();
        }
    }
}

