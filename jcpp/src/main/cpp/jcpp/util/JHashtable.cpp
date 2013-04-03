#include "JHashtable.h"
#include <sstream>
#include "JAbstractSet.h"
#include "Collections.h"
#include "JConcurrentModificationException.h"
#include "JNoSuchElementException.h"
#include "JInvalidObjectException.h"
#include "JCollections.h"

namespace jcpp{
    namespace util{
        static jint KEYS=0;
        static jint VALUES=1;
        static jint ENTRIES=2;

        class JHashtableClass : public JClass{
            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JHashtable* hashtable=(JHashtable*)object;
                hashtable->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                JHashtable* hashtable=(JHashtable*)object;
                hashtable->readObject((JObjectInputStream*)args->at(0));
                return NULL;
            }

            static JObject* staticGetThreshold(JObject* object){
                JHashtable* s=(JHashtable*)object;
                return s->threshold;
            }

            static void staticSetThreshold(JObject* object,JObject* value){
                JHashtable* s=(JHashtable*)object;
                delete s->threshold;
                s->threshold=(JPrimitiveInt*)value;
            }

            static JObject* staticGetLoadFactor(JObject* object){
                JHashtable* s=(JHashtable*)object;
                return s->loadFactor;
            }

            static void staticSetLoadFactor(JObject* object,JObject* value){
                JHashtable* s=(JHashtable*)object;
                delete s->loadFactor;
                s->loadFactor=(JPrimitiveFloat*)value;
            }

        public:
          JHashtableClass(){
              this->canonicalName="java.util.Hashtable";
              this->name="java.util.Hashtable";
              this->simpleName="Hashtable";
              this->serialVersionUID=1421746759512286392ULL;
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
              return JDictionary::getClazz();
          }

          JObject* newInstance(){
              return new JHashtable();
          }

          virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JHashtable::getClazz(){
            if (clazz==NULL){
                clazz=new JHashtableClass();
            }
            return clazz;
        }

        JHashtable::JHashtable(jint initialCapacity, jfloat loadFactor):JDictionary(getClazz()){
            init(initialCapacity,loadFactor);
        }

        JHashtable::JHashtable(JMap* m):JDictionary(getClazz()){
            init(m->size()*2,0.75);
            putAll(m);
        }

        void JHashtable::init(jint initialCapacity, jfloat loadFactor){
            this->loadFactor=new JPrimitiveFloat(loadFactor);
            if (initialCapacity < 0){
                throw new JIllegalArgumentException("Illegal initial capacity: ");
            }
            if (initialCapacity==0){
                initialCapacity = 1;
            }
            if (loadFactor <= 0){
                throw new JIllegalArgumentException("Illegal load factor: ");
            }
            this->threshold=new JPrimitiveInt(initialCapacity * loadFactor);
            table = new map<JObject*, JObject*, JObject::POINTER_COMPARATOR>();
        }

        jint JHashtable::size(){
            lock();
            jint i=table->size();
            unlock();
            return i;
        }

        jbool JHashtable::isEmpty(){
            lock();
            bool b=table->size()==0;
            unlock();
            return b;
        }

        JEnumeration* JHashtable::keys(){
            lock();
            JEnumeration* e=getEnumeration(KEYS);
            unlock();
            return e;
        }

        JEnumeration* JHashtable::elements(){
            lock();
            JEnumeration* e=getEnumeration(VALUES);
            unlock();
            return e;
        }

        jbool JHashtable::contains(JObject* value){
            if (value==NULL){
                throw new JNullPointerException();
            }
            lock();
            jbool b=hasValueFromMap(table,value);
            unlock();
            return b;
        }

        jbool JHashtable::containsValue(JObject* value){
            return contains(value);
        }

        jbool JHashtable::containsKey(JObject* key){
            return get(key) != NULL;
        }

        JObject* JHashtable::get(JObject* key){
            if (key==NULL){
                throw new JNullPointerException();
            }
            lock();
            JObject* value=getFromMap(table,key);
            unlock();
            return value;
        }

        JObject* JHashtable::put(JObject* key, JObject* value){
            if (key==NULL || value==NULL){
                throw new JNullPointerException();
            }
            lock();
            JObject* old=getAndDeleteFromMap(table,key);
            table->insert(pair<JObject*,JObject*>(key,value));
            modCount++;
            unlock();
            return old;
        }

        JObject* JHashtable::remove(JObject* key){
            if (key==NULL){
                throw new JNullPointerException();
            }
            lock();
            JObject* old=getAndDeleteFromMap(table,key);
            unlock();
            return old;
        }

        void JHashtable::putAll(JMap* m) {
            lock();
            JIterator* i=m->entrySet()->iterator();
            while (i->hasNext()){
                JEntry* e=dynamic_cast<JEntry*>(i->next());
                getAndDeleteFromMap(table,e->getKey());
                table->insert(pair<JObject*,JObject*>(e->getKey(),e->getValue()));
            }
            modCount++;
            delete i;
            unlock();
        }

        void JHashtable::clear(){
            lock();
            modCount++;
            table->clear();
            unlock();
        }

        JHashtable* JHashtable::clone(){
            JHashtable* h=new JHashtable(this);
            return h;
        }

        string JHashtable::toString(){
            jint max = size() - 1;
            if (max == -1){
                return "{}";
            }

            lock();
            stringstream ss;
            JIterator* it = entrySet()->iterator();
            ss<<'{';
            while (it->hasNext()) {
                JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(it->next());
                JObject* key = e->getKey();
                JObject* value = e->getValue();
                ss<<(key   == this ? "(this Map)" : key->toString());
                ss<<'=';
                ss<<(value == this ? "(this Map)" : value->toString());
                ss<<", ";
            }
            delete it;
            ss<<'}';
            unlock();
            return ss.str();
        }

        static JClass* hashtableKeySetImplClass;
        class JHashtableKeySetImpl : public JAbstractSet {
        protected:
            class JKeySetImplClass : public JClass{
            public:
              JKeySetImplClass(){
                  this->canonicalName="java.util.Hashtable$KeySet";
                  this->name="java.util.Hashtable$KeySet";
                  this->simpleName="Hashtable$KeySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashtable::getClazz();
              }
            };
            JHashtable* map;
        public:
            static JClass* getClazz(){
                if (hashtableKeySetImplClass==NULL){
                    hashtableKeySetImplClass=new JKeySetImplClass();
                }
                return hashtableKeySetImplClass;
            }

            JHashtableKeySetImpl(JHashtable* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return map->getIterator(KEYS);
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

        JSet* JHashtable::keySet(){
            return new JHashtableKeySetImpl(this);
        }

        static JClass* hashtableEntrySetClass;
        class JHashtableEntrySetImpl : public JAbstractSet{
        protected:
            class JEntrySetImplClass : public JClass{
            public:
              JEntrySetImplClass(){
                  this->canonicalName="java.util.Hashtable$EntrySet";
                  this->name="java.util.Hashtable$EntrySet";
                  this->simpleName="Hashtable$EntrySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashtable::getClazz();
              }
            };
            JHashtable* map;
        public:
            static JClass* getClazz(){
                if (hashtableEntrySetClass==NULL){
                    hashtableEntrySetClass=new JEntrySetImplClass();
                }
                return hashtableEntrySetClass;
            }

            JHashtableEntrySetImpl(JHashtable* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return map->getIterator(ENTRIES);
            }

            jbool add(JMap::JEntry* e){
                return JAbstractSet::add(dynamic_cast<JObject*>(e));
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

        JSet* JHashtable::entrySet(){
            return new JHashtableEntrySetImpl(this);
        }

        static JClass* hashtableValuesClass;
        class JHashtableValues : public JAbstractCollection {
        protected:
            class JValuesClass : public JClass{
            public:
              JValuesClass(){
                  this->canonicalName="java.util.Hashtable$ValueCollection";
                  this->name="java.util.Hashtable$ValueCollection";
                  this->simpleName="Hashtable$ValueCollection";
              }

              JClass* getSuperclass(){
                  return JAbstractCollection::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JHashtable::getClazz();
              }
            };
            JHashtable* map;
        public:
            static JClass* getClazz(){
                if (hashtableValuesClass==NULL){
                    hashtableValuesClass=new JValuesClass();
                }
                return hashtableValuesClass;
            }

            JHashtableValues(JHashtable* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return map->getIterator(VALUES);
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

        JCollection* JHashtable::values(){
            return new JHashtableValues(this);
        }

        jbool JHashtable::equals(JObject* o) {
            if (o == this){
                return true;
            }

            if (!(JMap::getClazz()->isAssignableFrom(o->getClass()))){
                return false;
            }
            JMap* t = dynamic_cast<JMap*>(o);
            if (t->size() != size()){
                return false;
            }
            lock();
            JIterator* i = entrySet()->iterator();
            try {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    JObject* key = e->getKey();
                    JObject* value = e->getValue();
                    if (value == NULL) {
                        if (!(t->get(key)==NULL && t->containsKey(key))){
                            delete i;
                            unlock();
                            return false;
                        }
                    } else {
                        if (!value->equals(t->get(key))){
                            delete i;
                            unlock();
                            return false;
                        }
                    }
                }
            } catch (JClassCastException* unused)   {
                delete i;
                unlock();
                return false;
            } catch (JNullPointerException* unused) {
                delete i;
                unlock();
                return false;
            }
            delete i;
            unlock();
            return true;
        }

        jint JHashtable::hashCode() {
            jint h = 0;
            if (size()== 0){
                return h;
            }
            lock();
            JIterator* i = entrySet()->iterator();
            while (i->hasNext()) {
                JEntry* e = dynamic_cast<JEntry*>(i->next());
                h+=e->hashCode();
            }
            delete i;
            unlock();
            return h;
        }

        void JHashtable::writeObject(JObjectOutputStream* out){//should do something to synchronize
            out->defaultWriteObject();
            out->writeInt(table->size());
            out->writeInt(table->size());
            JIterator* i = (table->size() > 0) ? entrySet()->iterator() : NULL;
            if (i!=NULL){
                while (i->hasNext()){
                    JEntry* e=dynamic_cast<JEntry*>(i->next());
                    out->writeObject(e->getKey());
                    out->writeObject(e->getValue());
                }
                delete i;
            }
        }

        void JHashtable::readObject(JObjectInputStream* in){
            in->defaultReadObject();
            in->readInt();

            jint mappings = in->readInt();
            if (mappings < 0){
                throw new JInvalidObjectException("Illegal mappings count");
            }
            for (int i=0; i<mappings; i++) {
                JObject* key = in->readObject();
                JObject* value = in->readObject();
                put(key, value);
            }
        }

        class JHashtableEntryImpl : public JMap::JEntry, public JObject{
        protected:
        class JEntryImplClass : public JClass{
        public:
            JEntryImplClass(){
                this->canonicalName="java.util.Hashtable$Entry";
                this->name="java.util.Hashtable$Entry";
                this->simpleName="Hashtable$Entry";
                addInterface(JEntry::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual JClass* getDeclaringClass(){
                return JHashtable::getClazz();
            }
        };
        map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator it;

        public:
            static JClass* getClazz();

            JHashtableEntryImpl(map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator it) :JObject(getClazz()){
                this->it=it;
            }

            virtual JObject* getKey() {
                return (*it).first;
            }

            virtual JObject* getValue() {
                return (*it).second;
            }

            virtual JObject* setValue(JObject* newValue) {
                if (newValue==NULL){
                    throw new JNullPointerException();
                }
                JObject* oldValue = (*it).second;
                (*it).second=newValue;
                return oldValue;
            }

            virtual jbool equals(JObject* o) {
                if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                    return false;
                }
                JEntry* e = dynamic_cast<JEntry*>(o);
                JObject* k1 = getKey();
                JObject* k2 = e->getKey();
                if (k1 == k2 || (k1 != NULL && k1->equals(k2))) {
                    JObject* v1 = getValue();
                    JObject* v2 = e->getValue();
                    if (v1 == v2 || (v1 != NULL && v1->equals(v2))){
                        return true;
                    }
                }
                return false;
            }

            virtual jint hashCode() {
                return (getKey()==NULL   ? 0 : getKey()->hashCode()) ^ (getValue()==NULL ? 0 : getValue()->hashCode());
            }

            virtual string toString() {
                return getKey()->toString() + "=" + getValue()->toString();
            }
        };

        static JClass* hashtableEntryImplClass;
        JClass* JHashtableEntryImpl::getClazz(){
            if (hashtableEntryImplClass==NULL){
                hashtableEntryImplClass=new JEntryImplClass();
            }
            return hashtableEntryImplClass;
        }

        static JClass* hashtableEnumeratorImplClazz;
        class JHashtableEnumeratorImpl: public JObject, public JEnumeration, public JIterator {
        protected:
            class JHashtableEnumeratorImplClass : public JClass{
            public:
                JHashtableEnumeratorImplClass(){
                    this->canonicalName="java.util.Hashtable$Enumerator";
                    this->name="java.util.Hashtable$Enumerator";
                    this->simpleName="Hashtable$Enumerator";
                    addInterface(JEnumeration::getClazz());
                    addInterface(JIterator::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                virtual JClass* getDeclaringClass(){
                    return JHashtable::getClazz();
                }
            };
            JHashtable* hashtable;
            jbool first;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator begin;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator current;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator previous;
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator end;
            jint type;
            jbool isIterator;
            jint expectedModCount;

        public:
            static JClass* getClazz(){
                if (hashtableEnumeratorImplClazz==NULL){
                    hashtableEnumeratorImplClazz=new JHashtableEnumeratorImplClass();
                }
                return hashtableEnumeratorImplClazz;
            }

            JHashtableEnumeratorImpl(JHashtable* hashtable,jint type, jbool isIterator):JObject(getClazz()) {
                this->hashtable=hashtable;
                this->type = type;
                this->isIterator = isIterator;
                this->expectedModCount = hashtable->modCount;
                begin=hashtable->table->begin();
                first=true;
                end=hashtable->table->end();
            }

            jbool hasMoreElements() {
                if (first){
                    return hashtable->size()>0;
                }
                return current!= end;
            }

            JObject* nextElement() {
                if (hashtable->modCount!= expectedModCount){
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
                if (type==KEYS){
                    return (*previous).first;
                }else if (type==VALUES){
                    return (*previous).second;
                }else{
                    return new JHashtableEntryImpl(previous);
                }
            }

            jbool hasNext() {
                return hasMoreElements();
            }

            JObject* next() {
                if (hashtable->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
                return nextElement();
            }

            void remove() {
                if (!first || hashtable->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                JObject* k = (*previous).first;
                hashtable->remove(k);
                expectedModCount = hashtable->modCount;
            }
        };

        JEnumeration* JHashtable::getEnumeration(int type) {
            if (size() == 0) {
                return JCollections::emptyEnumeration();
            } else {
                return new JHashtableEnumeratorImpl(this,type, false);
            }
        }

        JIterator* JHashtable::getIterator(jint type) {
            if (table->size()== 0) {
                return JCollections::emptyIterator();
            } else {
                return new JHashtableEnumeratorImpl(this,type, true);
            }
        }

        void JHashtableClass::fillDeclaredClasses(){
            addDeclaredClass(JHashtableKeySetImpl::getClazz());
            addDeclaredClass(JHashtableEntrySetImpl::getClazz());
            addDeclaredClass(JHashtableValues::getClazz());
            addDeclaredClass(JHashtableEntryImpl::getClazz());
            addDeclaredClass(JHashtableEntrySetImpl::getClazz());
            addDeclaredClass(JHashtableEnumeratorImpl::getClazz());
        }

        JHashtable::~JHashtable(){
            delete table;
            delete threshold;
            delete loadFactor;
        }
    }
}
