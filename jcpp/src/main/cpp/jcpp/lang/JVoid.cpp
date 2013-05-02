#include "JVoid.h"
#include "JInstantiationException.h"
using namespace std;

namespace jcpp{
    namespace lang{
        class JVoidClass : public JClass{
          public:
            JVoidClass(){
                this->canonicalName="java.lang.Void";
                this->name="java.lang.Void";
                this->simpleName="Void";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JVoid::getClazz(){
            if (clazz==NULL){
                clazz=new JVoidClass();
            }
            return clazz;
        }
    }
}

