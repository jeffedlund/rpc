#include "QObjectHolder.h"
#include "Collections.h"
using namespace jcpp::util;

namespace jcpp{
    namespace lang{

        QObjectHolder::QObjectHolder(){
            objects=new map<QObject*,Present*>();
        }

        static QObjectHolder* instance;

        QObjectHolder* QObjectHolder::getQObjectHolder(){
            if (instance==NULL){
                instance=new QObjectHolder();
                instance->start();
            }
            return instance;
        }

        void QObjectHolder::releaseOwner(QObject* obj){
            lock();
            obj->setParent(NULL);
            obj->moveToThread(thread);
            objects->insert(pair<QObject*,Present*>(obj,new Present()));
            unlock();
        }

        //TODO call on delete of objects
        void QObjectHolder::takeOwner(QObject* obj){
            lock();
            Present* p=getFromMap(objects,obj);
            if (p!=NULL){
                p->p=false;
                p->thread=QThread::currentThread();
                notifyAll();
                p=getFromMap(objects,obj);
                while (p!=NULL){
                    wait();
                    p=getFromMap(objects,obj);
                }
            }
            unlock();
        }

        void QObjectHolder::run(){
            while (true){
                lock();
                map<QObject*,Present*>::iterator it=objects->begin();
                for (;it!=objects->end();){
                    Present* p=(*it).second;
                    if (p!=NULL && !p->p){
                        QObject* qo=(*it).first;
                        qo->setParent(NULL);
                        qo->moveToThread(p->thread);
                        objects->erase(it++);
                    }else{
                        it++;
                    }
                }
                notifyAll();
                wait();
                unlock();
            }
        }
    }
}
