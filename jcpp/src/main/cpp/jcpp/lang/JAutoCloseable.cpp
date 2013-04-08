#include "JAutoCloseable.h"

namespace jcpp{
    namespace lang{
        class JAutoCloseableClass : public JClass{
          public:
            JAutoCloseableClass():JClass(){
                this->canonicalName="java.lang.AutoCloseable";
                this->name="java.lang.AutoCloseable";
                this->simpleName="AutoCloseable";
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JAutoCloseable::getClazz(){
            if (clazz==NULL){
                clazz=new JAutoCloseableClass();
            }
            return clazz;
        }

        JAutoCloseable::~JAutoCloseable(){
        }
    }
}
