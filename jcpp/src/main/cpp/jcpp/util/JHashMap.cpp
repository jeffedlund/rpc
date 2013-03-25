#include "JHashMap.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JNoSuchElementException.h"
#include "JConcurrentModificationException.h"
#include "JAbstractSet.h"
#include "JInvalidObjectException.h"

namespace jcpp{
    namespace util{
        static JClass* entryImplClass;
        JClass* JHashMap::JEntryImpl::getClazz(){
            if (entryImplClass==NULL){
                entryImplClass=new JEntryImplClass();
            }
            return entryImplClass;
        }

        class JHashMapClass : public JClass{
            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JHashMap* hashMap=(JHashMap*)object;
                hashMap->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                JHashMap* hashMap=(JHashMap*)object;
                hashMap->readObject((JObjectInputStream*)args->at(0));
                return NULL;
            }

            static JObject* staticGetThreshold(JObject* object){
                JHashMap* s=(JHashMap*)object;
                return s->threshold;
            }

            static void staticSetThreshold(JObject* object,JObject* value){
                JHashMap* s=(JHashMap*)object;
                delete s->threshold;
                s->threshold=(JPrimitiveInt*)value;
            }

            static JObject* staticGetLoadFactor(JObject* object){
                JHashMap* s=(JHashMap*)object;
                return s->loadFactor;
            }

            static void staticSetLoadFactor(JObject* object,JObject* value){
                JHashMap* s=(JHashMap*)object;
                delete s->loadFactor;
                s->loadFactor=(JPrimitiveFloat*)value;
            }

        public:
          JHashMapClass(){
              this->canonicalName="java.util.HashMap";
              this->name="java.util.HashMap";
              this->simpleName="HashMap";
              this->serialVersionUID=362498820763181265ULL;
              addInterface(JMap::getClazz());
              addInterface(JSerializable::getClazz());
              addInterface(JCloneable::getClazz());

              vector<JClass*>* paramType=new vector<JClass*>();
              paramType->push_back(JObjectInputStream::getClazz());
              addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));

              paramType=new vector<JClass*>;
              paramType->push_back(JObjectOutputStream::getClazz());
              addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));

              addField(new JField("threshold",JPrimitiveInt::getClazz(),staticGetThreshold,staticSetThreshold));
              addField(new JField("loadFactor",JPrimitiveFloat::getClazz(),staticGetLoadFactor,staticSetLoadFactor));
          }

          JClass* getSuperclass(){
              return JAbstractMap::getClazz();
          }

          JObject* newInstance(){
              return new JHashMap();
          }
        };

        static JClass* clazz;

        JClass* JHashMap::getClazz(){
            if (clazz==NULL){
                clazz=new JHashMapClass();
            }
            return clazz;
        }

        static jint DEFAULT_INITIAL_CAPACITY = 16;
        static jint MAXIMUM_CAPACITY = 1 << 30;
        static jfloat DEFAULT_LOAD_FACTOR = 0.75f;
        static JObject* NULL_KEY = new JObject();

        JHashMap::JHashMap(jint initialCapacity, jfloat loadFactor):JAbstractMap(getClazz()){
            init(initialCapacity,loadFactor);
        }

        JHashMap::JHashMap(JHashMap* m):JAbstractMap(getClazz()){
            jint s=((m->size() / DEFAULT_LOAD_FACTOR) + 1 ?  (m->size() / DEFAULT_LOAD_FACTOR) + 1 : DEFAULT_INITIAL_CAPACITY);
            init(s,DEFAULT_LOAD_FACTOR);
            putAll(dynamic_cast<JMap*>(m));
        }

        void JHashMap::init(jint initialCapacity, jfloat loadFactor){
            this->loadFactor=new JPrimitiveFloat(loadFactor);
            if (initialCapacity < 0){
                throw new JIllegalArgumentException("Illegal initial capacity: ");
            }
            if (initialCapacity > MAXIMUM_CAPACITY){
                initialCapacity = MAXIMUM_CAPACITY;
            }
            if (loadFactor <= 0){
                throw new JIllegalArgumentException("Illegal load factor: ");
            }
            jint capacity = 1;
            while (capacity < initialCapacity){
                capacity <<= 1;
            }
            this->threshold=new JPrimitiveInt((jint)(capacity * loadFactor< MAXIMUM_CAPACITY + 1 ? capacity * loadFactor : MAXIMUM_CAPACITY + 1));
            table = new map<JObject*, JObject*, JObject::POINTER_COMPARATOR>();
            init();
        }

        void JHashMap::init(){
        }

        jint JHashMap::size(){
            return table->size();
        }

        jbool JHashMap::isEmpty(){
            return table->size()==0;
        }

        JObject* JHashMap::get(JObject* key){
            if (key==NULL){
                key=NULL_KEY;
            }
            JObject* value=getFromMap(table,key);
            return value;
        }

        jbool JHashMap::containsKey(JObject* key){
            return get(key) != NULL;
        }

        JObject* JHashMap::put(JObject* key, JObject* value){
            if (key==NULL){
                key=NULL_KEY;
            }
            JObject* old=getAndDeleteFromMap(table,key);
            table->insert(pair<JObject*,JObject*>(key,value));
            modCount++;
            return old;
        }

        void JHashMap::putAll(JMap* m) {
            JIterator* i=m->entrySet()->iterator();
            while (i->hasNext()){
                JEntry* e=dynamic_cast<JEntry*>(i->next());
                put(e->getKey(), e->getValue());
            }
            delete i;
        }

        JObject* JHashMap::remove(JObject* key){
            if (key==NULL){
                key=NULL_KEY;
            }
            JObject* old=getAndDeleteFromMap(table,key);
            return old;
        }

        void JHashMap::clear(){
            modCount++;
            table->clear();
        }

        jbool JHashMap::containsValue(JObject* value){
            return hasValueFromMap(table,value);
        }

        JHashMap* JHashMap::clone(){
            return new JHashMap(this);
        }

        class JHashIterator : public JObject, public JIterator {
            JHashMap* hashMap;
            jint expectedModCount;
            jbool first;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator begin;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator current;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator end;

        public:
            JHashIterator(JHashMap* hashMap) {
                this->hashMap=hashMap;
                expectedModCount = hashMap->modCount;
                begin=hashMap->table->begin();
                first=true;
                end=hashMap->table->end();
            }

            jbool hasNext() {
                if (first){
                    return hashMap->size()>0;
                }
                return current!= end;
            }

            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator nextEntry() {
                if (hashMap->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                if (!hasNext()){
                    throw new JNoSuchElementException();
                }
                map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator result;
                if (first){
                    first=false;
                    current=begin;
                }
                result=current;
                current++;
                return result;
            }

            void remove() {
                if (hashMap->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                JObject* k = (*current).first;
                hashMap->remove(k);
                expectedModCount = hashMap->modCount;
            }
        };

        class JValueIterator : public JHashIterator {
        public:
            JValueIterator(JHashMap* hashMap):JHashIterator(hashMap){
            }

            JObject* next() {
                return (*nextEntry()).second;
            }
        };

        class JKeyIterator : public JHashIterator {
        public:
            JKeyIterator(JHashMap* hashMap):JHashIterator(hashMap){
            }
            JObject* next() {
                return (*nextEntry()).first;
            }
        };

        class JEntryIterator : public JHashIterator{
        public:
            JEntryIterator(JHashMap* hashMap):JHashIterator(hashMap){
            }
            JObject* next() {
                map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator i=nextEntry();
                return new JHashMap::JEntryImpl(i);
            }
        };

        JIterator* JHashMap::newKeyIterator()   {
            return new JKeyIterator(this);
        }

        JIterator* JHashMap::newValueIterator()   {
            return new JValueIterator(this);
        }

        JIterator* JHashMap::newEntryIterator()   {
            return new JEntryIterator(this);
        }

        static JClass* keySetImplClass;
        class JKeySetImpl : public JAbstractSet {
        protected:
            class JKeySetImplClass : public JClass{
            public:
              JKeySetImplClass(){
                  this->canonicalName="java.util.HashMap$KeySet";
                  this->name="java.util.HashMap$KeySet";
                  this->simpleName="HashMap$KeySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };
            JHashMap* map;
        public:
            static JClass* getClazz(){
                if (keySetImplClass==NULL){
                    keySetImplClass=new JKeySetImplClass();
                }
                return keySetImplClass;
            }

            JKeySetImpl(JHashMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return map->newKeyIterator();
            }

            jint size() {
                return map->size();
            }

            jbool contains(JObject* o) {
                return map->containsKey(o);
            }

            jbool remove(JObject* o) {
                return map->remove(o) != NULL;
            }

            void clear() {
                map->clear();
            }
        };

        JSet* JHashMap::keySet(){
            return new JKeySetImpl(this);
        }

        static JClass* valuesClass;
        class JValues : public JAbstractCollection {
        protected:
            class JValuesClass : public JClass{
            public:
              JValuesClass(){
                  this->canonicalName="java.util.HashMap$Values";
                  this->name="java.util.HashMap$Values";
                  this->simpleName="HashMap$Values";
              }

              JClass* getSuperclass(){
                  return JAbstractCollection::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };
            JHashMap* map;
        public:
            static JClass* getClazz(){
                if (valuesClass==NULL){
                    valuesClass=new JValuesClass();
                }
                return valuesClass;
            }

            JValues(JHashMap* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return map->newValueIterator();
            }

            jint size() {
                return map->size();
            }

            jbool contains(JObject* o) {
                return map->containsValue(o);
            }

            void clear() {
                map->clear();
            }
        };

        JCollection* JHashMap::values(){
            return new JValues(this);
        }

        static JClass* entrySetClass;
        class JEntrySetImpl : public JAbstractSet{
        protected:
            class JEntrySetImplClass : public JClass{
            public:
              JEntrySetImplClass(){
                  this->canonicalName="java.util.HashMap$EntrySet";
                  this->name="java.util.HashMap$EntrySet";
                  this->simpleName="HashMap$EntrySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              JObject* newInstance(){
                  throw new JInstantiationException("cannot instantiate object of class "+getName());
              }
            };
            JHashMap* map;
        public:
            static JClass* getClazz(){
                if (entrySetClass==NULL){
                    entrySetClass=new JEntrySetImplClass();
                }
                return entrySetClass;
            }

            JEntrySetImpl(JHashMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return map->newEntryIterator();
            }

            jbool contains(JObject* o) {
                if (!(JMap::JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                    return false;
                }
                JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(o);
                JObject* v1=map->get(e->getKey());
                return v1->equals(e->getValue());
            }

            jbool remove(JObject* o) {
                if (!(JMap::JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                    return false;
                }
                JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(o);
                return map->remove(e->getKey());
            }

            jint size() {
                return map->size();
            }

            void clear() {
                map->clear();
            }
        };

        JSet* JHashMap::entrySet(){
            return entrySet0();
        }

        JSet* JHashMap::entrySet0(){
            return new JEntrySetImpl(this);
        }

        void JHashMap::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeInt(table->size());
            out->writeInt(table->size());
            JIterator* i = (table->size() > 0) ? entrySet0()->iterator() : NULL;
            if (i!=NULL){
                while (i->hasNext()){
                    JEntry* e=dynamic_cast<JEntry*>(i->next());
                    out->writeObject(e->getKey());
                    out->writeObject(e->getValue());
                }
                delete i;
            }
        }

        void JHashMap::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            in->readInt();

            jint mappings = in->readInt();
            if (mappings < 0){
                throw new JInvalidObjectException("Illegal mappings count");
            }
            init();
            for (int i=0; i<mappings; i++) {
                JObject* key = in->readObject();
                JObject* value = in->readObject();
                put(key, value);
            }
        }

        JHashMap::~JHashMap(){
            delete table;
            delete threshold;
            delete loadFactor;
        }
    }
}

