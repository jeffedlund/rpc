#ifndef JHASHMAP_H
#define JHASHMAP_H

#include "JObject.h"
#include "JCollection.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractMap.h"
#include "JCPP.h"
#include "JCloneable.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JHashMap : public JAbstractMap, public JCloneable, public JSerializable{
        protected:
            class JEntryImpl : public JEntry, public JObject{
            protected:
            class JEntryImplClass : public JClass{
            public:
                JEntryImplClass(){
                    this->canonicalName="java.util.HashMap$Entry";
                    this->name="java.util.HashMap$Entry";
                    this->simpleName="HashMap$Entry";
                    addInterface(JEntry::getClazz());
                }

                JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                JObject* newInstance(){
                    throw new JInstantiationException("cannot instantiate object of class "+getName());
                }
            };
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator it;

            public:
                static JClass* getClazz();

                JEntryImpl(map<JObject*,JObject*,JObject::POINTER_COMPARATOR>::iterator it) :JObject(getClazz()){
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

            map<JObject*, JObject*, JObject::POINTER_COMPARATOR>* table;
            JPrimitiveInt* threshold;
            JPrimitiveFloat* loadFactor;
            jint modCount;
            void init(jint initialCapacity, jfloat loadFactor);
            JSet* entrySet0();
            JIterator* newKeyIterator();
            JIterator* newValueIterator();
            JIterator* newEntryIterator();
            friend class JEntryImpl;
            friend class JHashIterator;
            friend class JEntryIterator;
            friend class JHashMapKeySetImpl;
            friend class JHashMapValues;
            friend class JHashMapEntrySetImpl;
            friend class JHashMapClass;
            friend class JHashSet;

        public:
            JHashMap(jint initialCapacity = 10, jfloat loadFactor=0.75);
            JHashMap(JMap* c);
            static JClass* getClazz();
            virtual void init();
            virtual jint size();
            virtual bool isEmpty();
            virtual JObject* get(JObject* key);
            virtual jbool containsKey(JObject* key);
            virtual JObject* put(JObject* key, JObject* value);
            virtual void putAll(JMap* m);
            virtual JObject* remove(JObject* key);
            virtual void clear();
            virtual jbool containsValue(JObject* value);
            virtual JHashMap* clone();
            virtual JSet* keySet();
            virtual JCollection* values();
            virtual JSet* entrySet();
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            virtual ~JHashMap();
        };
    }
}
#endif // JHASHMAP_H
