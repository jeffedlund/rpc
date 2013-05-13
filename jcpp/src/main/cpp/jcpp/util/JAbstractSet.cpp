#include "JAbstractSet.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"
#include "JListIterator.h"
#include "JNoSuchElementException.h"
#include "JConcurrentModificationException.h"
#include "JRandomAccess.h"
#include "JClassCastException.h"
#include "JNullPointerException.h"
using namespace std;

namespace jcpp{
    namespace util{
        class JAbstractSetClass : public JClass{

        public:
          JAbstractSetClass(){
              this->canonicalName="java.util.AbstractSet";
              this->name="java.util.AbstractSet";
              this->simpleName="AbstractSet";
              addInterface(JSet::getClazz());
          }

          JClass* getSuperclass(){
              return JAbstractCollection::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JAbstractSet::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractSetClass();
            }
            return clazz;
        }

        JAbstractSet::JAbstractSet(JClass* _class):JAbstractCollection(_class){
        }

        JPrimitiveArray* JAbstractSet::toArray(){
            return JAbstractCollection::toArray();
        }

        jbool JAbstractSet::isEmpty(){
            return JAbstractCollection::isEmpty();
        }

        jbool JAbstractSet::add(JObject* e){
            return JAbstractCollection::add(e);
        }

        jbool JAbstractSet::remove(JObject* o){
            return JAbstractCollection::remove(o);
        }

        jbool JAbstractSet::containsAll(JCollection* c){
            return JAbstractCollection::containsAll(c);
        }

        jbool JAbstractSet::addAll(JCollection* c){
            return JAbstractCollection::addAll(c);
        }

        jbool JAbstractSet::retainAll(JCollection* c){
            return JAbstractCollection::retainAll(c);
        }

        jbool JAbstractSet::removeAll(JCollection* c){
            jbool modified = false;
            if (size() > c->size()) {
                JIterator* i = c->iterator();
                for (; i->hasNext(); ){
                    modified |= remove(i->next());
                }
                delete i;
            } else {
                JIterator* i = iterator();
                for (; i->hasNext(); ) {
                    if (c->contains(i->next())) {
                        i->remove();
                        modified = true;
                    }
                }
                delete i;
            }
            return modified;
        }

        jbool JAbstractSet::equals(JObject* o){
            if (o == this){
                return true;
            }
            if (!JSet::getClazz()->isAssignableFrom(o->getClass())){
                return false;
            }
            JSet* c = dynamic_cast<JSet*>(o);
            if (c->size() != size()){
                return false;
            }
            try {
                return containsAll(c);
            } catch (JClassCastException* unused)   {
                return false;
            } catch (JNullPointerException* unused) {
                return false;
            }
        }

        jint JAbstractSet::hashCode(){
            jint h = 0;
            JIterator* i = iterator();
            while (i->hasNext()) {
                JObject* obj = i->next();
                if (obj != NULL){
                    h += obj->hashCode();
                }
            }
            delete i;
            return h;
        }

        JAbstractSet::~JAbstractSet(){
        }
    }
}

