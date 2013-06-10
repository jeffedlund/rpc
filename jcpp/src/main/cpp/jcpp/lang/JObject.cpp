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
#include <memory>
#include "Collections.h"
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
            this->qmutex=new QMutex(QMutex::NonRecursive);
            this->waitCondition=new QWaitCondition();
            this->fromObject=new map<JObject*,JINT*>();
            this->toObject=new map<JObject*,JINT*>();
            this->memoryMutex=new recursive_mutex();
        }

        JObject::JObject(JClass* _class){
            this->_class=_class;
            this->qmutex=new QMutex(QMutex::NonRecursive);
            this->waitCondition=new QWaitCondition();
            this->fromObject=new map<JObject*,JINT*>();
            this->toObject=new map<JObject*,JINT*>();
            this->memoryMutex=new recursive_mutex();
        }

        JObject::JObject(jbool){
            this->qmutex=new QMutex(QMutex::NonRecursive);
            this->waitCondition=new QWaitCondition();
            this->fromObject=new map<JObject*,JINT*>();
            this->toObject=new map<JObject*,JINT*>();
            this->memoryMutex=new recursive_mutex();
        }

        void JObject::link(JObject* o){
            if (o!=NULL){
                memoryMutex->lock();
                JINT* i=getFromMap(toObject,o);
                if (i==NULL){
                    i=new JINT(0);
                    toObject->insert(pair<JObject*,JINT*>(o,i));
                }
                i->increment();

                JINT* j=getFromMap(o->fromObject,this);
                if (j==NULL){
                    j=new JINT(0);
                    o->fromObject->insert(pair<JObject*,JINT*>(this,j));
                }
                j->increment();
                memoryMutex->unlock();
            }
        }

        void JObject::unlink(JObject* o){
            if (o!=NULL){
                memoryMutex->lock();
                JINT* i=getFromMap(toObject,o);
                if (i!=NULL){
                    i->decrement();
                    if (i->getValue()==0){
                        toObject->erase(o);
                        delete i;
                    }
                }

                JINT* j=getFromMap(o->fromObject,this);
                if (j!=NULL){
                    j->decrement();
                    if (j->getValue()==0){
                        o->fromObject->erase(this);
                        delete j;
                        o->finalize();
                    }
                }
                memoryMutex->unlock();
            }
        }

        JClass* JObject::getClass(){
            return this->_class;
        }

        jbool JObject::operator==(JObject &other){
            return equals(&other);
        }

        jbool JObject::operator!=(JObject &other){
            return !equals(&other);
        }

        jbool JObject::isInstanceOf(JClass* c){
            if (c==NULL){
                throw new JNullPointerException();
            }
            return c->isAssignableFrom(getClass());
        }

        JString JObject::toString(){
            JString s=JString("");
            s<<getClass()->getName();
            s<<"@";
            s<<(jlong)this;
            return s;
        }

        void JObject::lock(){
            if (JThread::addObjectLocked(this)){
                qmutex->lock();
            }
        }

        void JObject::unlock(){
            if (JThread::removeObjectLocked(this)){
                qmutex->unlock();
            }
        }

        void JObject::wait(){//we don't lock/unlock here, but at the caller level
            waitCondition->wait(qmutex);
        }

        void JObject::wait(jlong time){
            waitCondition->wait(qmutex,time);
        }

        void JObject::notify(){
            waitCondition->wakeOne();
        }

        void JObject::notifyAll(){
            waitCondition->wakeAll();
        }

        void JObject::finalize(){
            memoryMutex->lock();
            if (fromObject->size()==0){
                vector<JObject*>* keys=getKeys(toObject);
                for (vector<JObject*>::size_type i=0;i<keys->size();i++){
                    unlink(keys->at(i));
                }
                delete keys;
                delete this;
            }
            memoryMutex->unlock();
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
            delete qmutex;
            delete waitCondition;
            delete fromObject;
            delete toObject;
            delete memoryMutex;
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

