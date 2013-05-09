#include "JObject.h"
#include "JClass.h"
#include "JClassLoader.h"
#include <sstream>
#include "JIllegalArgumentException.h"
#include "JCloneNotSupportedException.h"
#include "JCloneable.h"
#include "JThread.h"
#include "JNullPointerException.h"
#include "JString.h"
using namespace std;

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
            return equals(&other);
        }

        bool JObject::operator!=(JObject &other){
            return !(*this==other);
        }

        jbool JObject::isInstanceOf(JClass* c){
            if (c==NULL){
                throw new JNullPointerException();
            }
            return c->isAssignableFrom(getClass());
        }

        JString JObject::toString(){
            JString s;
            s<<getClass()->getName();
            s<<"@";
            s<<(jlong)this;
            return s;
        }

        void JObject::lock(){
            if (JThread::addObjectLocked(this)){
                mutex->lock();
            }
        }

        void JObject::unlock(){
            if (JThread::removeObjectLocked(this)){
                mutex->unlock();
            }
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

        jbool JObject::equals(JObject* o){
            if (o==NULL || getClass()!=o->getClass()){
                return false;
            }
            return this==o;
        }

        jint JObject::hashCode(){
            return (jint)this;
        }

        JObject* JObject::clone(){
             throw new JCloneNotSupportedException("not clonable "+toString());
        }

        JObject::~JObject(){
            delete mutex;
            delete waitCondition;
        }
    }
}
ostream& jcpp::lang::operator<<(ostream& os,jcpp::lang::JObject* o) {
    if (o==NULL){
        os<<"NULL";
    }else{
        os<<o->toString();
    }
    return os;
}

