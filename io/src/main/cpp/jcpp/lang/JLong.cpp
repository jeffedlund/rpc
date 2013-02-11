#include "JLong.h"
#include "JClass.h"
#include <QtGlobal>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace jcpp{
    namespace lang{
        class JLongClass : public JClass{
          public:
            JLongClass(){
                this->canonicalName="java.lang.Long";
                this->name="java.lang.Long";
                this->simpleName="Long";
                this->serialVersionUID=4290774380558885855ULL;
            }

            JClass* getSuperclass(){
                return JNumber::getClazz();
            }

            JObject* newInstance(){
                return new JLong(0);
            }
        };

        static JClass* clazz;

        JClass* JLong::getClazz(){
            if (clazz==NULL){
                clazz=new JLongClass();
            }
            return clazz;
        }

        JLong::JLong(qint64 value):JNumber(getClazz()){
            this->value=value;
        }

        JLong::JLong():JNumber(getClazz()){
            this->value=0;
        }

        void JLong::set(qint64 value){
            this->value=value;
        }

        qint64 JLong::get(){
            return value;
        }

        string JLong::toString(){
            stringstream ss;
            ss<<value;
            return ss.str();
        }

        JLong::~JLong(){
        }
    }
}
