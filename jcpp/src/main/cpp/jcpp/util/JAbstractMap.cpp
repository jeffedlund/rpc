#include "JAbstractMap.h"
#include "JClass.h"
#include <cstdio>
#include "JInstantiationException.h"
#include <sstream>
#include "JAbstractSet.h"
#include "JClassCastException.h"
#include "JNullPointerException.h"

namespace jcpp{
    namespace util{
        class JAbstractMapClass : public JClass{

        public:
          JAbstractMapClass(){
              this->canonicalName="java.util.AbstractMap";
              this->name="java.util.AbstractMap";
              this->simpleName="AbstractMap";
              addInterface(JMap::getClazz());
          }

          JClass* getSuperclass(){
              return JObject::getClazz();
          }

          virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JAbstractMap::getClazz(){
            if (clazz==NULL){
                clazz=new JAbstractMapClass();
            }
            return clazz;
        }

        static JClass* simpleEntryClazz=NULL;
        JClass* JAbstractMap::JSimpleEntry::getClazz(){
            if (simpleEntryClazz==NULL){
                simpleEntryClazz=new JSimpleEntryClass();
            }
            return simpleEntryClazz;
        }

        static JClass* simpleImmutableEntryClazz;
        JClass* JAbstractMap::JSimpleImmutableEntry::getClazz(){
            if (simpleImmutableEntryClazz==NULL){
                simpleImmutableEntryClazz=new JSimpleImmutableEntryClass();
            }
            return simpleImmutableEntryClazz;
        }

        JAbstractMap::JAbstractMap(JClass* _class):JObject(_class){
        }

        jint JAbstractMap::size(){
            return entrySet()->size();
        }

        jbool JAbstractMap::isEmpty(){
            return size()==0;
        }

        jbool JAbstractMap::containsValue(JObject* value){
            JIterator* i = entrySet()->iterator();
            if (value==NULL) {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getValue()==NULL){
                        delete i;
                        return true;
                    }
                }
            } else {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (value->equals(e->getValue())){
                        delete i;
                        return true;
                    }
                }
            }
            delete i;
            return false;
        }

        jbool JAbstractMap::containsKey(JObject* key){
            JIterator* i = entrySet()->iterator();
            if (key==NULL) {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getKey()==NULL){
                        delete i;
                        return true;
                    }
                }
            } else {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (key->equals(e->getKey())){
                        delete i;
                        return true;
                    }
                }
            }
            delete i;
            return false;
        }

        JObject* JAbstractMap::get(JObject* key){
            JIterator* i = entrySet()->iterator();
            if (key==NULL) {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getKey()==NULL){
                        JObject* o=e->getValue();
                        delete i;
                        return o;
                    }
                }
            } else {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (key->equals(e->getKey())){
                        JObject* o=e->getValue();
                        delete i;
                        return o;
                    }
                }
            }
            return NULL;
        }

        JObject* JAbstractMap::put(JObject*, JObject*){
            throw new JUnsupportedOperationException();
        }

        JObject* JAbstractMap::remove(JObject* key){
            JIterator* i = entrySet()->iterator();
            JEntry* correctEntry = NULL;
            if (key==NULL) {
                while (correctEntry==NULL && i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getKey()==NULL){
                        correctEntry = e;
                    }
                }
            } else {
                while (correctEntry==NULL && i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (key->equals(e->getKey())){
                        correctEntry = e;
                    }
                }
            }
            JObject* oldValue = NULL;
            if (correctEntry !=NULL) {
                oldValue = correctEntry->getValue();
                i->remove();
            }
            delete i;
            return oldValue;
        }

        void JAbstractMap::putAll(JMap* m){
            JIterator* i=m->entrySet()->iterator();
            while (i->hasNext()){
                JEntry* e = dynamic_cast<JEntry*>(i->next());
                put(e->getKey(), e->getValue());
            }
            delete i;
        }

        void JAbstractMap::clear(){
            entrySet()->clear();
        }

        static JClass* abstractSetIteratorImplClazz;
        class JAbstractSetIteratorImpl : public JIterator, public JObject{
        protected:
            class JAbstractSetIteratorImplClass : public JClass{
            public:
              JAbstractSetIteratorImplClass(){
                  this->canonicalName="java.util.AbstractMap$AbstractSet$Iterator";
                  this->name="java.util.AbstractMap$AbstractSet$Iterator";
                  this->simpleName="AbstractMap$AbstractSet$Iterator";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass();
            };

            JIterator* i;
        public:
            static JClass* getClazz(){
                if (abstractSetIteratorImplClazz==NULL){
                    abstractSetIteratorImplClazz=new JAbstractSetIteratorImplClass();
                }
                return abstractSetIteratorImplClazz;
            }

            JAbstractSetIteratorImpl(JAbstractMap* map):JObject(getClazz()){
                i=map->entrySet()->iterator();
            }

            virtual jbool hasNext() {
                return i->hasNext();
            }

            virtual JObject* next() {
                JMap::JEntry* e=dynamic_cast<JMap::JEntry*>(i->next());
                return e->getKey();
            }

            void remove() {
                i->remove();
            }

            ~JAbstractSetIteratorImpl(){
                delete i;
            }
        };

        static JClass* abstractSetImplClazz;
        class JAbstractSetImpl : public JAbstractSet{
        protected:
            JAbstractMap* map;
            class JAbstractSetImplClass : public JClass{
            public:
              JAbstractSetImplClass(){
                  this->canonicalName="java.util.AbstractMap$AbstractSet";
                  this->name="java.util.AbstractMap$AbstractSet";
                  this->simpleName="AbstractMap$AbstractSet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JAbstractMap::getClazz();
              }

              virtual void fillDeclaredClasses(){
                  addDeclaredClass(JAbstractSetIteratorImpl::getClazz());
              }
            };
        public:

            static JClass* getClazz(){
                if (abstractSetImplClazz==NULL){
                    abstractSetImplClazz=new JAbstractSetImplClass();
                }
                return abstractSetImplClazz;
            }

            JAbstractSetImpl(JAbstractMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return new JAbstractSetIteratorImpl(map);
            }

            virtual jint size() {
                return map->size();
            }

            virtual jbool isEmpty() {
                return map->isEmpty();
            }

            virtual void clear() {
                map->clear();
            }

            virtual jbool contains(JObject* k) {
                return map->containsKey(k);
            }
        };

        JClass* JAbstractSetIteratorImpl::JAbstractSetIteratorImplClass::getDeclaringClass(){
            return JAbstractSetImpl::getClazz();
        }

        JSet* JAbstractMap::keySet(){
            return new JAbstractSetImpl(this);
        }

        static JClass* abstractCollectionIteratorImplClazz;
        class JAbstractCollectionIteratorImpl : public JIterator, public JObject{
        protected:
            class JAbstractCollectionIteratorImplClass : public JClass{
            public:
              JAbstractCollectionIteratorImplClass(){
                  this->canonicalName="java.util.AbstractMap$AbstractCollection$Iterator";
                  this->name="java.util.AbstractMap$AbstractCollection$Iterator";
                  this->simpleName="AbstractMap$AbstractCollection$Iterator";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass();
            };

            JIterator* i;
        public:
            static JClass* getClazz(){
                if (abstractCollectionIteratorImplClazz==NULL){
                    abstractCollectionIteratorImplClazz=new JAbstractCollectionIteratorImplClass();
                }
                return abstractCollectionIteratorImplClazz;
            }

            JAbstractCollectionIteratorImpl(JAbstractMap* map):JObject(getClazz()){
                i=map->entrySet()->iterator();
            }

            virtual jbool hasNext() {
                return i->hasNext();
            }

            virtual JObject* next() {
                JMap::JEntry* e=dynamic_cast<JMap::JEntry*>(i->next());
                return e->getKey();
            }

            void remove() {
                i->remove();
            }

            ~JAbstractCollectionIteratorImpl(){
                delete i;
            }
        };

        static JClass* abstractCollectionImplClazz;
        class JAbstractCollectionImpl : public JAbstractCollection{
        protected:
            JAbstractMap* map;
            class JAbstractCollectionImplClass : public JClass{
            public:
              JAbstractCollectionImplClass(){
                  this->canonicalName="java.util.AbstractMap$AbstractCollection";
                  this->name="java.util.AbstractMap$AbstractCollection";
                  this->simpleName="AbstractMap$AbstractCollection";
              }

              JClass* getSuperclass(){
                  return JAbstractCollection::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JAbstractMap::getClazz();
              }

              virtual void fillDeclaredClasses(){
                  addDeclaredClass(JAbstractCollectionIteratorImpl::getClazz());
              }
            };
        public:

            static JClass* getClazz(){
                if (abstractCollectionImplClazz==NULL){
                    abstractCollectionImplClazz=new JAbstractCollectionImplClass();
                }
                return abstractCollectionImplClazz;
            }

            JAbstractCollectionImpl(JAbstractMap* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return new JAbstractCollectionIteratorImpl(map);
            }

            virtual jint size() {
                return map->size();
            }

            virtual jbool isEmpty() {
                return map->isEmpty();
            }

            virtual void clear() {
                map->clear();
            }

            virtual jbool contains(JObject* v) {
                return map->containsValue(v);
            }

            virtual jbool equals(JObject *o){
                return JObject::equals(o);
            }

            virtual jint hashCode(){
                return JObject::hashCode();
            }
        };

        JClass* JAbstractCollectionIteratorImpl::JAbstractCollectionIteratorImplClass::getDeclaringClass(){
            return JAbstractCollectionImpl::getClazz();
        }

        JCollection* JAbstractMap::values(){
            return new JAbstractCollectionImpl(this);
        }

        jbool JAbstractMap::equals(JObject* o){
            if (o == this){
                return true;
            }

            if (!JMap::getClazz()->isAssignableFrom(o->getClass())){
                 return false;
            }
            JMap* m=dynamic_cast<JMap*>(o);
            if (m->size() != size()){
                 return false;
            }
            JIterator* i = entrySet()->iterator();
            try {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    JObject* key = e->getKey();
                    JObject* value = e->getValue();
                    if (value == NULL) {
                        if (!(m->get(key)==NULL && m->containsKey(key))){
                            delete i;
                            return false;
                        }
                    } else {
                        JObject* v2=m->get(key);
                        if (v2==NULL || !value->equals(v2)){
                            delete i;
                            return false;
                        }
                    }
                }
            } catch (JClassCastException* unused) {
                delete i;
                return false;
            } catch (JNullPointerException* unused) {
                delete i;
                return false;
            }
            delete i;
            return true;
        }

        jint JAbstractMap::hashCode(){
            jint h = 0;
            JIterator* i = entrySet()->iterator();
            while (i->hasNext()){
                h += i->next()->hashCode();
            }
            delete i;
            return h;
        }

        JString JAbstractMap::toString(){
            JIterator* i = entrySet()->iterator();
            if (!i->hasNext()){
                delete i;
                return "{}";
            }

            JString ss;
            ss<<'{';
            for (;;) {
                JEntry* e = dynamic_cast<JEntry*>(i->next());
                JObject* key = e->getKey();
                JObject* value = e->getValue();
                ss<<(key   == this ? "(this Map)" : key->toString());
                ss<<'=';
                ss<<(value == this ? "(this Map)" : value->toString());
                if (! i->hasNext()){
                    delete i;
                    ss<<'}';
                    return ss;
                }
                ss<<','<<' ';
            }
        }

        void JAbstractMapClass::fillDeclaredClasses(){
            addDeclaredClass(JAbstractMap::JSimpleEntry::getClazz());
            addDeclaredClass(JAbstractMap::JSimpleImmutableEntry::getClazz());
            addDeclaredClass(JAbstractCollectionImpl::getClazz());
            addDeclaredClass(JAbstractSetImpl::getClazz());
        }

        JAbstractMap::~JAbstractMap(){
        }
    }
}
