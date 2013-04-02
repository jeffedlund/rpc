#include "JFuture.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JFutureClass : public JClass{

            public:
              JFutureClass(){
                  this->canonicalName="java.util.concurrent.Future";
                  this->name="java.util.concurrent.Future";
                  this->simpleName="Future";
                  this->bIsInterface=true;
              }

              JClass* getSuperclass(){
                  return JInterface::getClazz();
              }
            };

            static JClass* clazz;

            JClass* JFuture::getClazz(){
                if (clazz==NULL){
                    clazz=new JFutureClass();
                }
                return clazz;
            }

            JFuture::~JFuture(){
            }
        }
    }
}
