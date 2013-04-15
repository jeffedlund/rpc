#include "JCloseable.h"
#include "JClass.h"

namespace jcpp{
    namespace io{
        class JCloseableClass : public JClass{
            public:
                JCloseableClass(){
                    this->canonicalName="java.io.Closeable";
                    this->name="java.io.Closeable";
                    this->simpleName="Closeable";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JAutoCloseable::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JCloseable::getClazz(){
            if (clazz==NULL){
                clazz=new JCloseableClass();
            }
            return clazz;
        }

        JCloseable::~JCloseable(){
        }
    }
}
