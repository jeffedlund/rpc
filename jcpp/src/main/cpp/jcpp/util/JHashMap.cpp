#include "JHashMap.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JNoSuchElementException.h"
#include "JConcurrentModificationException.h"
#include "JAbstractSet.h"

namespace jcpp{
    namespace util{
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

            static JObject* staticGetSize(JObject* object){
                JHashMap* s=(JHashMap*)object;
                return NULL;
            }

            static void staticSetSize(JObject* object,JObject* value){
                JHashMap* s=(JHashMap*)object;
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

              addField(new JField("size",JPrimitiveInt::getClazz(),staticGetSize,staticSetSize));
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

        JHashMap::JHashMap(jint initialCapacity, jfloat loadFactor):JAbstractMap(getClazz()){
            init(initialCapacity,loadFactor);
        }

        JHashMap::JHashMap(JHashMap* m):JAbstractMap(getClazz()){
            jint s=((m->size() / DEFAULT_LOAD_FACTOR) + 1 ?  (m->size() / DEFAULT_LOAD_FACTOR) + 1 : DEFAULT_INITIAL_CAPACITY);
            init(s,DEFAULT_LOAD_FACTOR);
            putAll(dynamic_cast<JMap*>(m));
        }

        void JHashMap::init(jint initialCapacity, jfloat loadFactor){
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

            this->loadFactor = loadFactor;
            threshold = (jint)(capacity * loadFactor< MAXIMUM_CAPACITY + 1 ? capacity * loadFactor : MAXIMUM_CAPACITY + 1);
            table = new vector<JEntryImpl*>();
            init();
        }

        void JHashMap::init(){
        }

        static jint indexFor(jint h, jint length) {
            return h & (length-1);
        }

        jint JHashMap::size(){
            return isize;
        }

        jbool JHashMap::isEmpty(){
            return isize==0;
        }

        JObject* JHashMap::get(JObject* key){
            JEntry* entry = getEntry(key);
            return (entry==NULL ? NULL : entry->getValue());
        }

        jbool JHashMap::containsKey(JObject* key){
            return getEntry(key) != NULL;
        }

        JHashMap::JEntryImpl* JHashMap::getEntry(JObject* key) {
            jint hash = (key == NULL) ? 0 : key->hashCode();
            for (JEntryImpl* e = table->at(indexFor(hash, table->size())); e != NULL; e = e->next) {
                JObject* k;
                if (e->hash == hash && ((k = e->key) == key || (key != NULL && key->equals(k)))){
                    return e;
                }
            }
            return NULL;
        }

        JObject* JHashMap::put(JObject* key, JObject* value){
            if (key == NULL){
                return putForNullKey(value);
            }
            jint hash = key->hashCode();
            jint i = indexFor(hash, table->size());
            JEntryImpl* e = table->at(i);
            for(; e != NULL; e = e->next) {
                JObject* k;
                if (e->hash == hash && ((k = e->key) == key || key->equals(k))) {
                    JObject* oldValue = e->value;
                    e->value = value;
                    e->recordAccess(this);
                    return oldValue;
                }
            }

            modCount++;
            addEntry(hash, key, value, i);
            return NULL;
        }

        JObject* JHashMap::putForNullKey(JObject* value) {
            JEntryImpl* e = table->at(0);
            for(; e != NULL; e = e->next) {
                if (e->key == NULL) {
                    JObject* oldValue = e->value;
                    e->value = value;
                    e->recordAccess(this);
                    return oldValue;
                }
            }
            modCount++;
            addEntry(0, NULL, value, 0);
            return NULL;
        }

        void JHashMap::putForCreate(JObject* key, JObject* value) {
            jint hash = key == NULL ? 0 : key->hashCode();
            jint i = indexFor(hash, table->size());

            for (JEntryImpl* e = table->at(i); e != NULL; e = e->next) {
                JObject* k;
                if (e->hash == hash && ((k = e->key) == key || (key != NULL && key->equals(k)))) {
                    e->value = value;
                    return;
                }
            }

            createEntry(hash, key, value, i);
        }

        void JHashMap::putAll(JMap* m) {
            JIterator* i=m->entrySet()->iterator();
            while (i->hasNext()){
                JEntry* e=dynamic_cast<JEntry*>(i->next());
                put(e->getKey(), e->getValue());
            }
        }

        JObject* JHashMap::remove(JObject* key){
            JEntryImpl* e = removeEntryForKey(key);
            return (e == NULL ? NULL : e->value);
        }

        JHashMap::JEntryImpl* JHashMap::removeEntryForKey(JObject* key) {
            jint hash = (key == NULL) ? 0 : key->hashCode();
            jint i = indexFor(hash, table->size());
            JEntryImpl* prev = table->at(i);
            JEntryImpl* e = prev;

            while (e != NULL) {
                JEntryImpl* next = e->next;
                JObject* k;
                if (e->hash == hash && ((k = e->key) == key || (key != NULL && key->equals(k)))) {
                    modCount++;
                    isize--;
                    if (prev == e){
                        //TODO table->at(table->begin()+i) = next;
                    }else{
                        prev->next = next;
                    }
                    e->recordRemoval(this);
                    return e;
                }
                prev = e;
                e = next;
            }
            return e;
        }

        JHashMap::JEntryImpl* JHashMap::removeMapping(JObject* o) {
            if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                return NULL;
            }

            JEntry* entry = dynamic_cast<JEntry*>(o);
            JObject* key = entry->getKey();
            jint hash = (key == NULL) ? 0 : key->hashCode();
            jint i = indexFor(hash, table->size());
            JEntryImpl* prev = table->at(i);
            JEntryImpl* e = prev;

            while (e != NULL) {
                JEntryImpl* next = e->next;
                if (e->hash == hash && e->equals((JObject*)entry)) {
                    modCount++;
                    isize--;
                    if (prev == e){
                        //TODO (*table)[table->begin()+i] = next;
                    }else{
                        prev->next = next;
                    }
                    e->recordRemoval(this);
                    return e;
                }
                prev = e;
                e = next;
            }
            return e;
        }

        void JHashMap::clear(){
            modCount++;
            for (int i = 0; i < table->size(); i++){
                delete table->at(i);
            }
            table->clear();
            isize = 0;
        }

        jbool JHashMap::containsValue(JObject* value){
            if (value == NULL){
                return containsNullValue();
            }

            for (int i = 0; i < table->size(); i++){
                for (JEntryImpl* e = table->at(i) ; e != NULL ; e = e->next){
                    if (value->equals(e->value)){
                        return true;
                    }
                }
            }
            return false;
        }

        jbool JHashMap::containsNullValue() {
            for (int i = 0; i < table->size(); i++){
                for (JEntryImpl* e = table->at(i) ; e != NULL ; e = e->next){
                    if (e->value == NULL){
                        return true;
                    }
                }
            }
            return false;
        }

        JHashMap* JHashMap::clone(){
            return new JHashMap(this);
        }

        void JHashMap::addEntry(jint hash, JObject* key, JObject* value, jint bucketIndex) {
            createEntry(hash, key, value, bucketIndex);
        }

        void JHashMap::createEntry(jint hash, JObject* key, JObject* value, jint bucketIndex) {
            JEntryImpl* e = table->at(bucketIndex);
            //TODO table->at(table->begin()+bucketIndex) = new JEntryImpl(hash, key, value, e);
            isize++;
        }

        class JHashIterator : public JObject, public JIterator {
            JHashMap::JEntryImpl* next;
            jint expectedModCount;
            jint index;
            JHashMap::JEntryImpl* current;
            JHashMap* map;

        public:
            JHashIterator(JHashMap* map) {
                this->map=map;
                expectedModCount = map->modCount;
                if (map->size()> 0) {
                    while (index < map->table->size() && (next = map->table->at(index++)) == NULL){
                        ;
                    }
                }
            }

            jbool hasNext() {
                return next != NULL;
            }

            JHashMap::JEntryImpl* nextEntry() {
                if (map->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                JHashMap::JEntryImpl* e = next;
                if (e == NULL){
                    throw new JNoSuchElementException();
                }

                if ((next = e->next) == NULL) {
                    while (index < map->table->size() && (next = map->table->at(index++)) == NULL){
                        ;
                    }
                }
                current = e;
                return e;
            }

            void remove() {
                if (current == NULL){
                    throw new JIllegalStateException();
                }
                if (map->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                JObject* k = current->key;
                current = NULL;
                map->removeEntryForKey(k);
                expectedModCount = map->modCount;
            }
        };

        class JValueIterator : public JHashIterator {
        public:
            JValueIterator(JHashMap* m):JHashIterator(m){
            }

            JObject* next() {
                return nextEntry()->value;
            }
        };

        class JKeyIterator : public JHashIterator {
        public:
            JKeyIterator(JHashMap* m):JHashIterator(m){
            }
            JObject* next() {
                return nextEntry()->getKey();
            }
        };

        class JEntryIterator : public JHashIterator{
        public:
            JEntryIterator(JHashMap* m):JHashIterator(m){
            }
            JObject* next() {
                return nextEntry();
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

        class JKeySetImpl : public JAbstractSet {
        protected:
            JHashMap* map;
        public:
            JKeySetImpl(JHashMap* map):JAbstractSet(NULL){//TODO
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
                return map->removeEntryForKey(o) != NULL;
            }

            void clear() {
                map->clear();
            }
        };

        JSet* JHashMap::keySet(){
            JSet* ks = internalKeySet;
            return (ks != NULL ? ks : (internalKeySet = new JKeySetImpl(this)));
        }

        class JValues : public JAbstractCollection {
        protected:
            JHashMap* map;
        public:
            JValues(JHashMap* map):JAbstractCollection(NULL){//TODO
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
            JCollection* vs = internalValues;
            return (vs != NULL ? vs : (internalValues = new JValues(this)));
        }

        class JEntrySetImpl : public JAbstractSet{
        protected:
            JHashMap* map;
        public:
            JEntrySetImpl(JHashMap* map):JAbstractSet(NULL){//TODO
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
                JHashMap::JEntryImpl* candidate = map->getEntry(e->getKey());
                return candidate != NULL && candidate->equals(o);
            }

            jbool remove(JObject* o) {
                return map->removeMapping(o) != NULL;
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
            JSet* es = internalEntrySet;
            return es != NULL ? es : (internalEntrySet = new JEntrySetImpl(this));
        }

        void JHashMap::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeInt(table->size());
            out->writeInt(isize);
            JIterator* i = (isize > 0) ? entrySet0()->iterator() : NULL;
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
                throw "TODO";//TODOnew JInvalidObjectException("Illegal mappings count");
            }
            table = new vector<JEntryImpl*>();
            init();
            for (int i=0; i<mappings; i++) {
                JObject* key = in->readObject();
                JObject* value = in->readObject();
                putForCreate(key, value);
            }
        }

        JHashMap::~JHashMap(){
        }
    }
}

