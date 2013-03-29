#include "JThreadLocal.h"
#include "JInstantiationException.h"
#include <QCoreApplication>
#include "Collections.h"
#include "QObjectHolder.h"
using namespace std;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JThreadLocalClass : public JClass{
          public:
            JThreadLocalClass():JClass(){
                this->canonicalName="java.lang.ThreadLocal";
                this->name="java.lang.ThreadLocal";
                this->simpleName="ThreadLocal";
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JThreadLocal::getClazz(){
            if (clazz==NULL){
                clazz=new JThreadLocalClass();
            }
            return clazz;
        }

        JThreadLocal::JThreadLocal():JObject(getClazz()){
            threadStorage=new QThreadStorage<JObject*>();
            JObject* o=initialValue();
            if (o!=NULL){
                threadStorage->setLocalData(o);
            }
        }

        JThreadLocal::JThreadLocal(JClass* _class):JObject(_class){
            threadStorage=new QThreadStorage<JObject*>();
            JObject* o=initialValue();
            if (o!=NULL){
                threadStorage->setLocalData(o);
            }
        }

        JObject* JThreadLocal::initialValue(){
            return NULL;
        }

        JObject* JThreadLocal::get(){
            if (threadStorage->hasLocalData()){
                return threadStorage->localData();
            }else{
                return NULL;
            }
        }

        void JThreadLocal::remove(){
        }

        void JThreadLocal::set(JObject* value){
            threadStorage->setLocalData(value);
        }

        JThreadLocal::~JThreadLocal(){
            delete threadStorage;
        }
    }
}

