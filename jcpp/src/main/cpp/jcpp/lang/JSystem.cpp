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

        void JSystem::arraycopy(jbyte src[],jint srcPos, jbyte dest[], jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest[destPos+i]=src[srcPos+i];
            }
        }

        void JSystem::arraycopy(jchar src[],jint srcPos, jchar dest[], jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest[destPos+i]=src[srcPos+i];
            }
        }

        void JSystem::arraycopy(string src,jint srcPos, jchar dest[], jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest[destPos+i]=(jchar)src.at(srcPos+i);
            }
        }

        void JSystem::arraycopy(JString* src,jint srcPos, jchar dest[], jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest[destPos+i]=(jchar)src->getString().at(srcPos+i);
            }
        }
    }
}

