#include "JIdentityHashMap.h"
#include "JClass.h"
#include <cstdio>
#include "Collections.h"
#include "JNoSuchElementException.h"
#include "JConcurrentModificationException.h"
#include "JAbstractSet.h"
#include "JInvalidObjectException.h"

namespace jcpp{
    namespace util{

        static JClass* identityHashMapEntryImplClass;
        class JIdentityHashMapEntryImpl : public JMap::JEntry, public JObject{
        protected:
        class JIdentityHashMapEntryImplClass : public JClass{
        public:
            JIdentityHashMapEntryImplClass(){
                this->canonicalName="java.util.IdentityHashMap$EntryIterator$Entry";
                this->name="java.util.IdentityHashMap$EntryIterator$Entry";
                this->simpleName="IdentityHashMap$EntryIterator$Entry";
                addInterface(JMap::JEntry::getClazz());
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual JClass* getDeclaringClass();
        };
        map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator it;

        public:
            static JClass* getClazz(){
                if (identityHashMapEntryImplClass==NULL){
                    identityHashMapEntryImplClass=new JIdentityHashMapEntryImplClass();
                }
                return identityHashMapEntryImplClass;
            }

            JIdentityHashMapEntryImpl(map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator it) :JObject(getClazz()){
                this->it=it;
            }

            virtual JObject* getKey() {
                return (*it).first;
            }

            virtual JObject* getValue() {
                return (*it).second;
            }

            virtual JObject* setValue(JObject* newValue) {
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
                if (k1 == k2 || (k1 != NULL && k1==k2)) {
                    JObject* v1 = getValue();
                    JObject* v2 = e->getValue();
                    if (v1 == v2 || (v1 != NULL && v1==v2)){
                        return true;
                    }
                }
                return false;
            }

            virtual jint hashCode() {
                return (getKey()==NULL   ? 0 : (jint)getKey()) ^ (getValue()==NULL ? 0 : (jint)getValue());
            }

            virtual JString toString() {
                return getKey()->toString() + "=" + getValue()->toString();
            }
        };

        class JIdentityHashMapClass : public JClass{
            static JObject* invokeWriteObject(JObject* object,vector<JObject*>* args){
                JIdentityHashMap* identityHashMap=(JIdentityHashMap*)object;
                identityHashMap->writeObject((JObjectOutputStream*)args->at(0));
                return NULL;
            }

            static JObject* invokeReadObject(JObject* object,vector<JObject*>* args){
                JIdentityHashMap* identityHashMap=(JIdentityHashMap*)object;
                identityHashMap->readObject((JObjectInputStream*)args->at(0));
                return NULL;
            }

            static JObject* staticGetSize(JObject* object){
                JIdentityHashMap* s=(JIdentityHashMap*)object;
                s->size();
                return s->isize;
            }

            static void staticSetSize(JObject*,JObject*){
            }

        public:
          JIdentityHashMapClass(){
              this->canonicalName="java.util.IdentityHashMap";
              this->name="java.util.IdentityHashMap";
              this->simpleName="IdentityHashMap";
              this->serialVersionUID=8188218128353913216ULL;
              addInterface(JMap::getClazz());
              addInterface(JSerializable::getClazz());
              addInterface(JCloneable::getClazz());

              vector<JClass*>* paramType=new vector<JClass*>();
              paramType->push_back(JObjectInputStream::getClazz());
              addMethod(new JMethod("readObject",this,JVoid::getClazz(),paramType,invokeReadObject));

              paramType=new vector<JClass*>;
              paramType->push_back(JObjectOutputStream::getClazz());
              addMethod(new JMethod("writeObject",this,JVoid::getClazz(),paramType,invokeWriteObject));

              addField(new JField("size",JPrimitiveInt::getClazz(),this,staticGetSize,staticSetSize));
          }

          JClass* getSuperclass(){
              return JAbstractMap::getClazz();
          }

          JObject* newInstance(){
              return new JIdentityHashMap();
          }

          virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JIdentityHashMap::getClazz(){
            if (clazz==NULL){
                clazz=new JIdentityHashMapClass();
            }
            return clazz;
        }

        static JObject* NULL_KEY = new JObject();

        JIdentityHashMap::JIdentityHashMap(jint):JAbstractMap(getClazz()){
            init();
        }

        JIdentityHashMap::JIdentityHashMap(JMap* m):JAbstractMap(getClazz()){
            init();
            putAll(m);
        }

        void JIdentityHashMap::init(){
            modCount=0;
            isize=new JPrimitiveInt(0);
            table = new map<JObject*, JObject*, JObject::POINTER_ID_COMPARATOR>();
        }

        jint JIdentityHashMap::size(){
            isize->set(table->size());
            return table->size();
        }

        jbool JIdentityHashMap::isEmpty(){
            return table->size()==0;
        }

        JObject* JIdentityHashMap::get(JObject* key){
            if (key==NULL){
                key=NULL_KEY;
            }
            JObject* value=getFromMap(table,key);
            return value;
        }

        jbool JIdentityHashMap::containsKey(JObject* key){
            return get(key) != NULL;
        }

        jbool JIdentityHashMap::containsValue(JObject* value){
            return hasValueFromMap(table,value);
        }

        JObject* JIdentityHashMap::put(JObject* key, JObject* value){
            if (key==NULL){
                key=NULL_KEY;
            }
            JObject* old=getAndDeleteFromMap(table,key);
            table->insert(pair<JObject*,JObject*>(key,value));
            modCount++;
            return old;
        }

        void JIdentityHashMap::putAll(JMap* m) {
            JIterator* i=m->entrySet()->iterator();
            while (i->hasNext()){
                JEntry* e=dynamic_cast<JEntry*>(i->next());
                put(e->getKey(), e->getValue());
            }
            delete i;
        }

        JObject* JIdentityHashMap::remove(JObject* key){
            if (key==NULL){
                key=NULL_KEY;
            }
            JObject* old=getAndDeleteFromMap(table,key);
            return old;
        }

        void JIdentityHashMap::clear(){
            modCount++;
            table->clear();
        }

        JIdentityHashMap* JIdentityHashMap::clone(){
            return new JIdentityHashMap(this);
        }

        static JClass* identityHashMapIteratorClass;
        class JIdentityHashMapIterator : public JObject, public JIterator {
        protected:
            class JIdentityHashMapIteratorClass : public JClass{
            public:
              JIdentityHashMapIteratorClass(){
                  this->canonicalName="java.util.IdentityHashMap$IdentityHashMapIterator";
                  this->name="java.util.IdentityHashMap$IdentityHashMapIterator";
                  this->simpleName="IdentityHashMap$IdentityHashMapIterator";
                  addInterface(JIterator::getClazz());
              }

              JClass* getSuperclass(){
                  return JObject::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }
            };
            JIdentityHashMap* identityHashMap;
            jint expectedModCount;
            jbool first;
            map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator begin;
            map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator previous;
            map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator current;
            map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator end;

            JIdentityHashMapIterator(JClass* _class,JIdentityHashMap* identityHashMap):JObject(_class) {
                this->identityHashMap=identityHashMap;
                expectedModCount = identityHashMap->modCount;
                begin=identityHashMap->table->begin();
                first=true;
                end=identityHashMap->table->end();
            }

        public:
            static JClass* getClazz(){
                if (identityHashMapIteratorClass==NULL){
                    identityHashMapIteratorClass=new JIdentityHashMapIteratorClass();
                }
                return identityHashMapIteratorClass;
            }

            JIdentityHashMapIterator(JIdentityHashMap* identityHashMap):JObject(getClazz()) {
                this->identityHashMap=identityHashMap;
                expectedModCount = identityHashMap->modCount;
                begin=identityHashMap->table->begin();
                first=true;
                end=identityHashMap->table->end();
            }

            jbool hasNext() {
                if (first){
                    return identityHashMap->size()>0;
                }
                return current!= end;
            }

            map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator nextEntry() {
                if (identityHashMap->modCount!= expectedModCount){
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
                if (!first || identityHashMap->modCount!= expectedModCount){
                    throw new JConcurrentModificationException();
                }
                JObject* k = (*previous).first;
                identityHashMap->remove(k);
                expectedModCount = identityHashMap->modCount;
            }
        };

        static JClass* identityHashMapValueIteratorClass;
        class JIdentityHashMapValueIterator : public JIdentityHashMapIterator {
        protected:
            class JIdentityHashMapValueIteratorClass : public JClass{
            public:
              JIdentityHashMapValueIteratorClass(){
                  this->canonicalName="java.util.IdentityHashMap$ValueIterator";
                  this->name="java.util.IdentityHashMap$ValueIterator";
                  this->simpleName="IdentityHashMap$ValueIterator";
              }

              JClass* getSuperclass(){
                  return JIdentityHashMapIterator::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }
            };
        public:
            static JClass* getClazz(){
                if (identityHashMapValueIteratorClass==NULL){
                    identityHashMapValueIteratorClass=new JIdentityHashMapValueIteratorClass();
                }
                return identityHashMapValueIteratorClass;
            }

            JIdentityHashMapValueIterator(JIdentityHashMap* identityHashMap):JIdentityHashMapIterator(getClazz(),identityHashMap){
            }

            JObject* next() {
                return (*nextEntry()).second;
            }
        };

        static JClass* identityHashMapKeyIteratorClass;
        class JIdentityHashMapKeyIterator : public JIdentityHashMapIterator {
        protected:
            class JIdentityHashMapKeyIteratorClass : public JClass{
            public:
              JIdentityHashMapKeyIteratorClass(){
                  this->canonicalName="java.util.IdentityHashMap$KeyIterator";
                  this->name="java.util.IdentityHashMap$KeyIterator";
                  this->simpleName="IdentityHashMap$KeyIterator";
              }

              JClass* getSuperclass(){
                  return JIdentityHashMapIterator::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }
            };
        public:
            static JClass* getClazz(){
                if (identityHashMapKeyIteratorClass==NULL){
                    identityHashMapKeyIteratorClass=new JIdentityHashMapKeyIteratorClass();
                }
                return identityHashMapKeyIteratorClass;
            }

            JIdentityHashMapKeyIterator(JIdentityHashMap* identityHashMap):JIdentityHashMapIterator(getClazz(),identityHashMap){
            }

            JObject* next() {
                JObject* o=(*nextEntry()).first;
                if (o==NULL_KEY){
                    return NULL;
                }
                return o;
            }
        };

        static JClass* identityHashMapEntryIteratorClass;
        class JIdentityHashMapEntryIterator : public JIdentityHashMapIterator{
        protected:
            class JIdentityHashMapEntryIteratorClass : public JClass{
            public:
              JIdentityHashMapEntryIteratorClass(){
                  this->canonicalName="java.util.IdentityHashMap$EntryIterator";
                  this->name="java.util.IdentityHashMap$EntryIterator";
                  this->simpleName="IdentityHashMap$EntryIterator";
              }

              JClass* getSuperclass(){
                  return JIdentityHashMapIterator::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }

              virtual void fillDeclaredClasses(){
                  addDeclaredClass(JIdentityHashMapEntryImpl::getClazz());
              }
            };
        public:
            static JClass* getClazz(){
                if (identityHashMapEntryIteratorClass==NULL){
                    identityHashMapEntryIteratorClass=new JIdentityHashMapEntryIteratorClass();
                }
                return identityHashMapEntryIteratorClass;
            }

            JIdentityHashMapEntryIterator(JIdentityHashMap* identityHashMap):JIdentityHashMapIterator(getClazz(),identityHashMap){
            }

            JObject* next() {
                map<JObject*,JObject*,JObject::POINTER_ID_COMPARATOR>::iterator i=nextEntry();
                return new JIdentityHashMapEntryImpl(i);
            }
        };

        JClass* JIdentityHashMapEntryImpl::JIdentityHashMapEntryImplClass::getDeclaringClass(){
            return JIdentityHashMapEntryIterator::getClazz();
        }

        static JClass* identityHashMapKeySetImplClass;
        class JIdentityHashMapKeySetImpl : public JAbstractSet {
        protected:
            class JIdentityHashMapKeySetImplClass : public JClass{
            public:
              JIdentityHashMapKeySetImplClass(){
                  this->canonicalName="java.util.IdentityHashMap$KeySet";
                  this->name="java.util.IdentityHashMap$KeySet";
                  this->simpleName="IdentityHashMap$KeySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }
            };
            JIdentityHashMap* map;
        public:
            static JClass* getClazz(){
                if (identityHashMapKeySetImplClass==NULL){
                    identityHashMapKeySetImplClass=new JIdentityHashMapKeySetImplClass();
                }
                return identityHashMapKeySetImplClass;
            }

            JIdentityHashMapKeySetImpl(JIdentityHashMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return new JIdentityHashMapKeyIterator(map);
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

        JSet* JIdentityHashMap::keySet(){
            return new JIdentityHashMapKeySetImpl(this);
        }

        static JClass* identityHashMapValuesClass;
        class JIdentityHashMapValues : public JAbstractCollection {
        protected:
            class JIdentityHashMapValuesClass : public JClass{
            public:
              JIdentityHashMapValuesClass(){
                  this->canonicalName="java.util.IdentityHashMap$Values";
                  this->name="java.util.IdentityHashMap$Values";
                  this->simpleName="IdentityHashMap$Values";
              }

              JClass* getSuperclass(){
                  return JAbstractCollection::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }
            };
            JIdentityHashMap* map;
        public:
            static JClass* getClazz(){
                if (identityHashMapValuesClass==NULL){
                    identityHashMapValuesClass=new JIdentityHashMapValuesClass();
                }
                return identityHashMapValuesClass;
            }

            JIdentityHashMapValues(JIdentityHashMap* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return new JIdentityHashMapValueIterator(map);
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

        JCollection* JIdentityHashMap::values(){
            return new JIdentityHashMapValues(this);
        }

        static JClass* identityHashMapEntrySetClass;
        class JIdentityHashMapEntrySetImpl : public JAbstractSet{
        protected:
            class JIdentityHashMapEntrySetImplClass : public JClass{
            public:
              JIdentityHashMapEntrySetImplClass(){
                  this->canonicalName="java.util.IdentityHashMap$EntrySet";
                  this->name="java.util.IdentityHashMap$EntrySet";
                  this->simpleName="IdentityHashMap$EntrySet";
              }

              JClass* getSuperclass(){
                  return JAbstractSet::getClazz();
              }

              virtual JClass* getDeclaringClass(){
                  return JIdentityHashMap::getClazz();
              }
            };
            JIdentityHashMap* map;
        public:
            static JClass* getClazz(){
                if (identityHashMapEntrySetClass==NULL){
                    identityHashMapEntrySetClass=new JIdentityHashMapEntrySetImplClass();
                }
                return identityHashMapEntrySetClass;
            }

            JIdentityHashMapEntrySetImpl(JIdentityHashMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            JIterator* iterator() {
                return new JIdentityHashMapEntryIterator(map);
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

        JSet* JIdentityHashMap::entrySet(){
            return new JIdentityHashMapEntrySetImpl(this);
        }

        void JIdentityHashMap::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
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

        void JIdentityHashMap::readObject(JObjectInputStream* in){
            in->defaultReadObject();

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

        void JIdentityHashMapClass::fillDeclaredClasses(){
            addDeclaredClass(JIdentityHashMapEntrySetImpl::getClazz());
            addDeclaredClass(JIdentityHashMapValues::getClazz());
            addDeclaredClass(JIdentityHashMapKeySetImpl::getClazz());
            addDeclaredClass(JIdentityHashMapEntryIterator::getClazz());
            addDeclaredClass(JIdentityHashMapKeyIterator::getClazz());
            addDeclaredClass(JIdentityHashMapValueIterator::getClazz());
            addDeclaredClass(JIdentityHashMapIterator::getClazz());
        }

        JIdentityHashMap::~JIdentityHashMap(){
            delete isize;
            delete table;
        }
    }
}


