#include "JCollections.h"
#include "JClass.h"
#include "JInstantiationException.h"
#include <cstdio>
#include "JRandomAccess.h"
#include "JCollection.h"
#include "JNoSuchElementException.h"
#include "JNullPointerException.h"
#include "JIllegalStateException.h"
#include "JObjectOutputStream.h"

namespace jcpp{
    namespace util{
        class JCollectionsClass : public JClass{

        public:
            JCollectionsClass(){
                this->canonicalName="java.util.Collections";
                this->name="java.util.Collections";
                this->simpleName="Collections";
                this->serialVersionUID=0;
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JCollections::getClazz(){
            if (clazz==NULL){
                clazz=new JCollectionsClass();
            }
            return clazz;
        }

        static JClass* synchronizedCollectionClazz;

        class JSynchronizedCollection : public JObject, public JCollection, public JSerializable {
        protected:
            class JSynchronizedCollectionClass : public JClass{

            public:
              JSynchronizedCollectionClass(){
                  this->canonicalName="java.util.Collections$SynchronizedCollection";
                  this->name="java.util.Collections$SynchronizedCollection";
                  this->simpleName="Collections$SynchronizedCollection";
                  addInterface(JSerializable::getClazz());
                  addInterface(JCollection::getClazz());
                  this->serialVersionUID=3053995032091335093ULL;
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JCollections::getClazz();
              }
            };
            JCollection* c;
            JObject* mutex;

        public:
            static JClass* getClazz(){
                if (synchronizedCollectionClazz==NULL){
                    synchronizedCollectionClazz=new JSynchronizedCollectionClass();
                }
                return synchronizedCollectionClazz;
            }

            JSynchronizedCollection(JCollection* c):JObject(getClazz()) {
                if (c==NULL){
                    throw new JNullPointerException();
                }
                this->c = c;
                mutex = this;
            }

            JSynchronizedCollection(JClass* _class,JCollection* c):JObject(_class) {
                if (c==NULL){
                    throw new JNullPointerException();
                }
                this->c = c;
                mutex = this;
            }

            JSynchronizedCollection(JClass* _class,JCollection* c, JObject* mutex):JObject(_class){
                this->c = c;
                this->mutex = mutex;
            }

            JSynchronizedCollection(JCollection* c, JObject* mutex):JObject(getClazz()){
                this->c = c;
                this->mutex = mutex;
            }

            int size() {
                mutex->lock();
                jint p=c->size();
                mutex->unlock();
                return p;
            }

            bool isEmpty() {
                mutex->lock();
                bool b=c->isEmpty();
                mutex->unlock();
                return b;
            }

            bool contains(JObject* o) {
                mutex->lock();
                bool b=c->contains(o);
                mutex->unlock();
                return b;
            }

            JIterator* iterator() {
                return c->iterator();
            }

            bool add(JObject* e) {
                mutex->lock();
                bool b=c->add(e);
                mutex->unlock();
                return b;
            }

            bool remove(JObject* o) {
                mutex->lock();
                bool b=c->remove(o);
                mutex->unlock();
                return b;
            }

            bool containsAll(JCollection* coll) {
                mutex->lock();
                bool b=c->containsAll(coll);
                mutex->unlock();
                return b;
            }

            bool addAll(JCollection* coll) {
                mutex->lock();
                bool b=c->addAll(coll);
                mutex->unlock();
                return b;
            }

            bool removeAll(JCollection* coll) {
                mutex->lock();
                bool b=c->removeAll(coll);
                mutex->unlock();
                return b;
            }

            bool retainAll(JCollection* coll) {
                mutex->lock();
                bool b=c->retainAll(coll);
                mutex->unlock();
                return b;
            }

            JPrimitiveArray* toArray(){
                mutex->lock();
                JPrimitiveArray* a=c->toArray();
                mutex->unlock();
                return a;
            }

            void clear() {
                mutex->lock();
                c->clear();
                mutex->unlock();
            }

            JString toString() {
                mutex->lock();
                JObject* o=dynamic_cast<JObject*>(c);
                JString s=o->toString();
                mutex->unlock();
                return s;
            }

            void writeObject(JObjectOutputStream* s){
                mutex->lock();
                s->defaultWriteObject();
                mutex->unlock();
            }
        };


        static JClass* synchronizedListClazz;
        class JSynchronizedList : public JSynchronizedCollection, public JList{
        protected:
            class JSynchronizedListClass : public JClass{

            public:
              JSynchronizedListClass(){
                  this->canonicalName="java.util.Collections$SynchronizedList";
                  this->name="java.util.Collections$SynchronizedList";
                  this->simpleName="Collections$SynchronizedList";
                  this->serialVersionUID=-7754090372962971524ULL;
                  addInterface(JList::getClazz());
              }

              JClass* getSuperclass(){
                  return JSynchronizedCollection::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JCollections::getClazz();
              }
            };
            JList* list;
        public:
            static JClass* getClazz(){
                if (synchronizedListClazz==NULL){
                    synchronizedListClazz=new JSynchronizedListClass();
                }
                return synchronizedListClazz;
            }

            JSynchronizedList(JList* list):JSynchronizedCollection(getClazz(),list){
                this->list = list;
            }

            JSynchronizedList(JClass* _class,JList* list):JSynchronizedCollection(_class,list){
                this->list = list;
            }

            JSynchronizedList(JList* list, JObject* mutex):JSynchronizedCollection(getClazz(),list,mutex){
                this->list = list;
            }

            JSynchronizedList(JClass* _class,JList* list, JObject* mutex):JSynchronizedCollection(_class,list,mutex){
                this->list = list;
            }

            int size() {
                return JSynchronizedCollection::size();
            }

            bool isEmpty() {
                return JSynchronizedCollection::isEmpty();
            }

            bool contains(JObject* o) {
                return JSynchronizedCollection::contains(o);
            }

            bool add(JObject* e){
                return JSynchronizedCollection::add(e);
            }

            bool remove(JObject* o){
                return JSynchronizedCollection::remove(o);
            }

            bool containsAll(JCollection* c){
                return JSynchronizedCollection::containsAll(c);
            }

            bool addAll(JCollection* c){
                return JSynchronizedCollection::addAll(c);
            }

            bool removeAll(JCollection* c){
                return JSynchronizedCollection::removeAll(c);
            }

            bool retainAll(JCollection* c){
                return JSynchronizedCollection::retainAll(c);
            }

            JPrimitiveArray* toArray(){
                return JSynchronizedCollection::toArray();
            }

            void clear(){
                return JSynchronizedCollection::clear();
            }

            bool equals(JObject* o) {
                if (o==this){
                    return true;
                }
                mutex->lock();
                bool b=list->equals(o);
                mutex->unlock();
                return b;
            }

            jint hashCode() {
                mutex->lock();
                jint h=list->hashCode();
                mutex->unlock();
                return h;
            }

            JObject* get(jint index) {
                mutex->lock();
                JObject* o=list->get(index);
                mutex->unlock();
                return o;
            }

            JObject* set(jint index, JObject* element) {
                mutex->lock();
                JObject* o=list->set(index, element);
                mutex->unlock();
                return o;
            }

            void add(jint index, JObject* element) {
                mutex->lock();
                list->add(index, element);
                mutex->unlock();
            }

            JObject* remove(jint index) {
                mutex->lock();
                JObject* o=list->remove(index);
                mutex->unlock();
                return o;
            }

            jint indexOf(JObject* o) {
                mutex->lock();
                jint i=list->indexOf(o);
                mutex->unlock();
                return i;
            }

            jint lastIndexOf(JObject* o) {
                mutex->lock();
                jint i=list->lastIndexOf(o);
                mutex->unlock();
                return i;
            }

            bool addAll(jint index, JCollection* c) {
                mutex->lock();
                bool b=list->addAll(index, c);
                mutex->unlock();
                return b;
            }

            JIterator* iterator(){
                return JSynchronizedCollection::iterator();
            }

            JListIterator* listIterator() {
                return list->listIterator();
            }

            JListIterator* listIterator(jint index) {
                return list->listIterator(index);
            }

            JList* subList(jint fromIndex, jint toIndex) {
                mutex->lock();
                JList* l=new JSynchronizedList(list->subList(fromIndex, toIndex),mutex);
                mutex->unlock();
                return l;
            }
        };

        static JClass* synchronizedRandomAccessListClazz;
        class JSynchronizedRandomAccessList : public JSynchronizedList, public JRandomAccess{
        protected:
            class JSynchronizedRandomAccessListClass : public JClass{

            public:
              JSynchronizedRandomAccessListClass(){
                  this->canonicalName="java.util.Collections$SynchronizedRandomAccessList";
                  this->name="java.util.Collections$SynchronizedRandomAccessList";
                  this->simpleName="Collections$SynchronizedRandomAccessList";
                  addInterface(JRandomAccess::getClazz());
                  this->serialVersionUID=1530674583602358482ULL;
              }

              JClass* getSuperclass(){
                  return JSynchronizedList::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JCollections::getClazz();
              }
            };

        public:
            static JClass* getClazz(){
                if (synchronizedRandomAccessListClazz==NULL){
                    synchronizedRandomAccessListClazz=new JSynchronizedRandomAccessListClass();
                }
                return synchronizedRandomAccessListClazz;
            }

            JSynchronizedRandomAccessList(JList* list):JSynchronizedList(getClazz(),list) {
            }

            JSynchronizedRandomAccessList(JList* list, JObject* mutex):JSynchronizedList(getClazz(),list,mutex) {
            }

           JList* subList(jint fromIndex, jint toIndex) {
               mutex->lock();
               JList* l=new JSynchronizedRandomAccessList(list->subList(fromIndex, toIndex), mutex);
               mutex->unlock();
               return l;
            }
        };

        JList* JCollections::synchronizedList(JList* list) {
            JObject* o=dynamic_cast<JObject*>(list);
            return (JRandomAccess::getClazz()->isAssignableFrom(o->getClass()) ? new JSynchronizedRandomAccessList(list) : new JSynchronizedList(list));
        }

        static JClass* emptyIteratorClazz;
        class JEmptyIterator : public JObject, public JIterator{
        protected:
            class JEmptyIteratorClass : public JClass{

            public:
              JEmptyIteratorClass(){
                  this->canonicalName="java.util.Collections$EmptyIterator";
                  this->name="java.util.Collections$EmptyIterator";
                  this->simpleName="Collections$EmptyIterator";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JCollections::getClazz();
              }
            };

        public:
            static JClass* getClazz(){
                if (emptyIteratorClazz==NULL){
                    emptyIteratorClazz=new JEmptyIteratorClass();
                }
                return emptyIteratorClazz;
            }

            JEmptyIterator():JObject(getClazz()){
            }

            bool hasNext(){
                return false;
            }

            JObject* next(){
                throw new JNoSuchElementException();
            }

            void remove(){
                throw new JIllegalStateException();
            }

            ~JEmptyIterator(){
            }
        };


        JIterator* JCollections::emptyIterator(){
            return new JEmptyIterator();
        }

        static JClass* emptyEnumerationClazz;
        class JEmptyEnumeration : public JObject, public JEnumeration{
        protected:
            class JEmptyEnumerationClass : public JClass{

            public:
              JEmptyEnumerationClass(){
                  this->canonicalName="java.util.Collections$EmptyEnumeration";
                  this->name="java.util.Collections$EmptyEnumeration";
                  this->simpleName="Collections$EmptyEnumeration";
                  addInterface(JEnumeration::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JCollections::getClazz();
              }
            };
        public:
            static JClass* getClazz(){
                if (emptyEnumerationClazz==NULL){
                    emptyEnumerationClazz=new JEmptyEnumerationClass();
                }
                return emptyEnumerationClazz;
            }

            JEmptyEnumeration():JObject(getClazz()){
            }

            bool hasMoreElements(){
                return false;
            }

            JObject* nextElement(){
                throw new JNoSuchElementException();
            }


            ~JEmptyEnumeration(){
            }
        };

        JEnumeration* JCollections::emptyEnumeration(){
            return new JEmptyEnumeration();
        }

        void JCollectionsClass::fillDeclaredClasses(){
            addDeclaredClass(JSynchronizedCollection::getClazz());
            addDeclaredClass(JSynchronizedList::getClazz());
            addDeclaredClass(JSynchronizedRandomAccessList::getClazz());
            addDeclaredClass(JEmptyIterator::getClazz());
            addDeclaredClass(JEmptyEnumeration::getClazz());
        }

        JCollections::~JCollections(){
        }
    }
}

