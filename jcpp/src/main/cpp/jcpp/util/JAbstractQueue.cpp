#include "JAbstractQueue.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"
#include "JNoSuchElementException.h"
#include "JIllegalStateException.h"
#include "JNullPointerException.h"
#include "JIllegalArgumentException.h"
using namespace std;

namespace jcpp{
    namespace util{
        class JAbstractQueueClass : public JClass{

        public:
          JAbstractQueueClass(){
              this->canonicalName="java.util.AbstractQueue";
              this->name="java.util.AbstractQueue";
              this->simpleName="AbstractQueue";
              addInterface(JQueue::getClazz());
          }

          JClass* getSuperclass(){
              return JAbstractCollection::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JAbstractQueue::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractQueueClass();
            }
            return clazz;
        }

        JAbstractQueue::JAbstractQueue(JClass* _class):JAbstractCollection(_class){
        }

        bool JAbstractQueue::add(JObject* e){
            if (offer(e)){
                return true;
            }else{
                throw new JIllegalStateException("Queue full");
            }
        }

        JObject* JAbstractQueue::remove(){
            JObject* x=poll();
            if (x!=NULL){
                return x;
            }else{
                throw new JNoSuchElementException();
            }

        }

        JObject* JAbstractQueue::element(){
            JObject* x=peek();
            if (x!=NULL){
                return x;
            }else{
                throw new JNoSuchElementException();
            }
        }

        void JAbstractQueue::clear(){
            while (poll()!=NULL){
                ;
            }
        }

        jbool JAbstractQueue::addAll(JCollection* c){
            if (c == NULL){
                throw new JNullPointerException();
            }
            if (c == (JAbstractCollection*)this){
                throw new JIllegalArgumentException();
            }
            jbool modified = false;
            JIterator* i=c->iterator();
            while (i->hasNext()){
                JObject* e=i->next();
                if (add(e)){
                    modified = true;
                }
            }
            delete i;
            return modified;
        }

        JAbstractQueue::~JAbstractQueue(){
        }
    }
}
