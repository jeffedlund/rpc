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

              addField(new JField("threshold",JPrimitiveInt::getClazz(),this,staticGetThreshold,staticSetThreshold));
              addField(new JField("loadFactor",JPrimitiveFloat::getClazz(),this,staticGetLoadFactor,staticSetLoadFactor));
          }

          JClass* getSuperclass(){
              return JAbstractMap::getClazz();
          }

          JObject* newInstance(){
              return new JHashMap();
          }

          virtual void fillDeclaredClasses();
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

        JHashMap::JHashMap(JMap* m):JAbstractMap(getClazz()){
            jint s=((m->size() / DEFAULT_LOAD_FACTOR) + 1 ?  (m->size() / DEFAULT_LOAD_FACTOR) + 1 : DEFAULT_INITIAL_CAPACITY);
            init(s,DEFAULT_LOAD_FACTOR);
            putAll(m);
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

        static JClass* hashMapHashIteratorClass;
        class JHashIterator : public JObject, public JIterator {
        protected:
            class JHashIteratorClass : public JClass{
            public:
              JHashIteratorClass(){
                  this->canonicalName="java.util.HashMap$HashIterator";
                  this->name="java.util.HashMap$HashIterator";
                  this->simpleName="HashMap$HashIterator";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
            JHashMap* hashMap;
            jint expectedModCount;
            jbool first;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator begin;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator previous;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator current;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator end;
            JHashIterator(JClass* _class,JHashMap* hashMap):JObject(_class) {
                this->hashMap=hashMap;
                expectedModCount = hashMap->modCount;
                begin=hashMap->table->begin();
                first=true;
                end=hashMap->table->end();
            }

        public:
            static JClass* getClazz(){
                if (hashMapHashIteratorClass==NULL){
                    hashMapHashIteratorClass=new JHashIteratorClass();
                }
                return hashMapHashIteratorClass;
            }

            JHashIterator(JHashMap* hashMap):JObject(getClazz()) {
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
                if (first){
                    first=false;
                    current=begin;
                }
                previous=current;
                current++;
                return previous;
            }

            void remove() {
                if (!first || hashMap->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                JObject* k = (*previous).first;
                hashMap->remove(k);
                expectedModCount = hashMap->modCount;
            }
        };

        static JClass* hashMapValueIteratorClass;
        class JValueIterator : public JHashIterator {
        protected:
            class JValueIteratorClass : public JClass{
            public:
              JValueIteratorClass(){
                  this->canonicalName="java.util.HashMap$ValueIterator";
                  this->name="java.util.HashMap$ValueIterator";
                  this->simpleName="HashMap$ValueIterator";
              }

              JClass* getSuperclass(){
                  return JHashIterator::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
        public:
            static JClass* getClazz(){
                if (hashMapValueIteratorClass==NULL){
                    hashMapValueIteratorClass=new JValueIteratorClass();
                }
                return hashMapValueIteratorClass;
            }

            JValueIterator(JHashMap* hashMap):JHashIterator(getClazz(),hashMap){
            }

            JObject* next() {
                return (*nextEntry()).second;
            }
        };

        static JClass* hashMapKeyIteratorClass;
        class JKeyIterator : public JHashIterator {
        protected:
            class JKeyIteratorClass : public JClass{
            public:
              JKeyIteratorClass(){
                  this->canonicalName="java.util.HashMap$KeyIterator";
                  this->name="java.util.HashMap$KeyIterator";
                  this->simpleName="HashMap$KeyIterator";
              }

              JClass* getSuperclass(){
                  return JHashIterator::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
        public:
            static JClass* getClazz(){
                if (hashMapKeyIteratorClass==NULL){
                    hashMapKeyIteratorClass=new JKeyIteratorClass();
                }
                return hashMapKeyIteratorClass;
            }

            JKeyIterator(JHashMap* hashMap):JHashIterator(getClazz(),hashMap){
            }

            JObject* next() {
                return (*nextEntry()).first;
            }
        };

        static JClass* hashMapEntryIteratorClass;
        class JEntryIterator : public JHashIterator{
        protected:
            class JEntryIteratorClass : public JClass{
            public:
              JEntryIteratorClass(){
                  this->canonicalName="java.util.HashMap$EntryIterator";
                  this->name="java.util.HashMap$EntryIterator";
                  this->simpleName="HashMap$EntryIterator";
              }

              JClass* getSuperclass(){
                  return JHashIterator::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
        public:
            static JClass* getClazz(){
                if (hashMapEntryIteratorClass==NULL){
                    hashMapEntryIteratorClass=new JEntryIteratorClass();
                }
                return hashMapEntryIteratorClass;
            }

            JEntryIterator(JHashMap* hashMap):JHashIterator(getClazz(),hashMap){
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

        static JClass* hashMapKeySetImplClass;
        class JHashMapKeySetImpl : public JAbstractSet {
        protected:
            class JHashMapKeySetImplClass : public JClass{
            public:
              JHashMapKeySetImplClass(){
                  this->canonicalName="java.util.HashMap$KeySet";
                  this->name="java.util.HashMap$KeySet";
                  this->simpleName="HashMap$KeySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
            JHashMap* map;
        public:
            static JClass* getClazz(){
                if (hashMapKeySetImplClass==NULL){
                    hashMapKeySetImplClass=new JHashMapKeySetImplClass();
                }
                return hashMapKeySetImplClass;
            }

            JHashMapKeySetImpl(JHashMap* map):JAbstractSet(getClazz()){
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
            return new JHashMapKeySetImpl(this);
        }

        static JClass* hashMapValuesClass;
        class JHashMapValues : public JAbstractCollection {
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

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
            JHashMap* map;
        public:
            static JClass* getClazz(){
                if (hashMapValuesClass==NULL){
                    hashMapValuesClass=new JValuesClass();
                }
                return hashMapValuesClass;
            }

            JHashMapValues(JHashMap* map):JAbstractCollection(getClazz()){
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
            return new JHashMapValues(this);
        }

        static JClass* hashMapEntrySetClass;
        class JHashMapEntrySetImpl : public JAbstractSet{
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

              virtual JClass* getDeclaringClass(){
                  return JHashMap::getClazz();
              }
            };
            JHashMap* map;
        public:
            static JClass* getClazz(){
                if (hashMapEntrySetClass==NULL){
                    hashMapEntrySetClass=new JEntrySetImplClass();
                }
                return hashMapEntrySetClass;
            }

            JHashMapEntrySetImpl(JHashMap* map):JAbstractSet(getClazz()){
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
            return new JHashMapEntrySetImpl(this);
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

        void JHashMapClass::fillDeclaredClasses(){
            addDeclaredClass(JHashIterator::getClazz());
            addDeclaredClass(JValueIterator::getClazz());
            addDeclaredClass(JKeyIterator::getClazz());
            addDeclaredClass(JEntryIterator::getClazz());
            addDeclaredClass(JHashMapKeySetImpl::getClazz());
            addDeclaredClass(JHashMapValues::getClazz());
            addDeclaredClass(JHashMapEntrySetImpl::getClazz());
            addDeclaredClass(JHashMap::JEntryImpl::getClazz());
        }

        JHashMap::~JHashMap(){
            delete table;
            delete threshold;
            delete loadFactor;
        }
    }
}

