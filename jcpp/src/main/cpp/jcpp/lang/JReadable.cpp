#include "JReadable.h"
#include "JClass.h"

namespace jcpp{
    namespace lang{
        class JReadableClass : public JClass{
            public:
                JReadableClass(){
                    this->canonicalName="java.lang.Readable";
                    this->name="java.lang.Readable";
                    this->simpleName="Readable";
                    this->bIsInterface=true;
                }

                JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static JClass* clazz;

        JClass* JReadable::getClazz(){
            if (clazz==NULL){
                clazz=new JReadableClass();
            }
            return clazz;
        }

        JReadable::~JReadable(){
        }
    }
}
