#include "JNumber.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JNumberClass : public JClass{
          public:
            JNumberClass(){
                this->canonicalName="java.lang.Number";
                this->name="java.lang.Number";
                this->simpleName="Number";
                this->serialVersionUID=-8742448824652078965ULL;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            JObject* newInstance(){
                throw new JInstantiationException("cannot instantiate object of class "+getName());
            }
        };

        JNumber::JNumber(JClass* _class):JObject(_class){
        }

        static JClass* clazz;

        JClass* JNumber::getClazz(){
            if (clazz==NULL){
                clazz=new JNumberClass();
            }
            return clazz;
        }
    }
}
