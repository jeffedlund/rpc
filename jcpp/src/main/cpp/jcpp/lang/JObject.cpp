#include "JObject.h"
#include "JClass.h"
#include "JClassLoader.h"
#include <sstream>
#include "JIllegalArgumentException.h"

namespace jcpp{
    namespace lang{
        class JObjectClass : public JClass{
            public:
                JObjectClass():JClass(){
                    canonicalName="java.lang.Objet";
                    name="java.lang.Object";
                    simpleName="Object";
                }

                JClass* getSuperclass(){
                    return NULL;
                }

                JObject* newInstance(){
                    return new JObject();
                }
        };

        static JClass* clazz;

        JClass* JObject::getClazz(){
            if (clazz==NULL){
                clazz=new JObjectClass();
            }
            return clazz;
        }

        JObject::JObject(){
            this->_class=JObject::getClazz();
            this->mutex=new QMutex(QMutex::NonRecursive);
            this->waitCondition=new QWaitCondition();
        }


        JObject::JObject(JClass* _class){
            this->_class=_class;
            this->mutex=new QMutex(QMutex::NonRecursive);
            this->waitCondition=new QWaitCondition();
        }

        JObject::JObject(bool){
            this->mutex=new QMutex(QMutex::NonRecursive);
            this->waitCondition=new QWaitCondition();
        }

        JClass* JObject::getClass(){
            return this->_class;
        }

        bool JObject::operator==(JObject &other){
            if (getClass()!=other.getClass()){
                return false;
            }
            return this==&other;
        }

        string JObject::toString(){
            stringstream ss;
            ss<<getClass()->getName();
            ss<<"@";
            ss<<(this);
            return ss.str();
        }

        void JObject::lock(){
            mutex->lock();
        }

        void JObject::unlock(){
            mutex->unlock();
        }

        void JObject::wait(){//we don't lock/unlock here, but at the caller level
            waitCondition->wait(mutex);
        }

        void JObject::wait(jlong time){
            waitCondition->wait(mutex,time);
        }

        void JObject::notify(){
            waitCondition->wakeOne();
        }

        void JObject::notifyAll(){
            waitCondition->wakeAll();
        }

        JObject* JObject::clone(){
            throw new JIllegalArgumentException("not clonable "+toString());//TODO better clone layer
        }

        JObject::~JObject(){
            delete mutex;
            delete waitCondition;
        }
    }
}
