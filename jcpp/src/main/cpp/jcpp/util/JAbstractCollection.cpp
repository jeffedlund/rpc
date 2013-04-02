#include "JAbstractCollection.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"
#include <sstream>

namespace jcpp{
    namespace util{
        class JAbstractCollectionClass : public JClass{

        public:
          JAbstractCollectionClass(){
              this->canonicalName="java.util.AbstractCollection";
              this->name="java.util.AbstractCollection";
              this->simpleName="AbstractCollection";
              this->serialVersionUID=0;
              addInterface(JCollection::getClazz());
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JAbstractCollection::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractCollectionClass();
            }
            return clazz;
        }

        JAbstractCollection::JAbstractCollection(JClass* _class):JObject(_class){
        }

        bool JAbstractCollection::isEmpty(){
            return size()==0;
        }

        bool JAbstractCollection::contains(JObject* o){
            JIterator* e = iterator();
            if (o==NULL) {
                while (e->hasNext()){
                    if (e->next()==NULL){
                        delete e;
                        return true;
                    }
                }
            } else {
                while (e->hasNext())
                if (o->equals(e->next())){
                    delete e;
                    return true;
                }
            }
            delete e;
            return false;
        }


        JPrimitiveArray* JAbstractCollection::toArray(){
            JClass* _class=NULL;
            JPrimitiveArray* r=NULL;
            JIterator* it = iterator();
            if (it->hasNext()){
                JObject* o=it->next();
                _class=o->getClass();
                r=new JPrimitiveArray(_class,size());
            }
            for (int i = 1; i < r->size(); i++) {
                it->hasNext();
                JObject* o=it->next();
                r->set(i,o);
            }
            delete it;
            return r;
        }

        bool JAbstractCollection::add(JObject*){
            throw new JUnsupportedOperationException();
        }

        bool JAbstractCollection::remove(JObject* o) {
            JIterator* e = iterator();
            if (o==NULL) {
                while (e->hasNext()) {
                    if (e->next()==NULL) {
                        e->remove();
                        delete e;
                        return true;
                    }
                }
            } else {
                while (e->hasNext()) {
                    if (o->equals(e->next())) {
                        e->remove();
                        delete e;
                        return true;
                    }
                }
            }
            delete e;
            return false;
        }

        bool JAbstractCollection::containsAll(JCollection* c){
            JIterator* e = c->iterator();
            while (e->hasNext()){
                if (!contains(e->next())){
                    delete e;
                    return false;
                }
            }
            delete e;
            return true;
        }

        bool JAbstractCollection::addAll(JCollection* c){
            bool modified = false;
            JIterator* e = c->iterator();
            while (e->hasNext()) {
                if (add(e->next())){
                    modified = true;
                }
            }
            delete e;
            return modified;
        }

        bool JAbstractCollection::removeAll(JCollection* c){
            bool modified = false;
            JIterator* e = iterator();
            while (e->hasNext()) {
                if (c->contains(e->next())) {
                    e->remove();
                    modified = true;
                }
            }
            delete e;
            return modified;
        }

        bool JAbstractCollection::retainAll(JCollection* c){
            bool modified = false;
            JIterator* e = iterator();
            while (e->hasNext()) {
                if (!c->contains(e->next())) {
                    e->remove();
                    modified = true;
                }
            }
            delete e;
            return modified;
        }

        void JAbstractCollection::clear(){
            JIterator* e = iterator();
            while (e->hasNext()) {
                e->next();
                e->remove();
            }
            delete e;
        }

        string JAbstractCollection::toString(){
            JIterator* i = iterator();
            if (! i->hasNext()){
                delete i;
                return "[]";
            }

            stringstream ss;
            ss<<'[';
            for (;;) {
                JObject* o= i->next();
                ss<<(o == this ? "(this Collection)" : o->toString());
                if (! i->hasNext()){
                    delete i;
                    ss<<']';
                    return ss.str();
                }
                ss<<", ";
            }
        }

        JAbstractCollection::~JAbstractCollection(){
        }
    }
}
