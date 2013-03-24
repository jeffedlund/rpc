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

            public:
                JObject* key;
                JObject*  value;
                JEntryImpl* next;
                jint hash;

                JEntryImpl(jint h, JObject* k, JObject* v, JEntryImpl* n) {
                    value = v;
                    next = n;
                    key = k;
                    hash = h;
                }

                virtual JObject* getKey() {
                    return key;
                }

                virtual JObject* getValue() {
                    return value;
                }

                virtual JObject* setValue(JObject* newValue) {
                    JObject* oldValue = value;
                    value = newValue;
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
                    return (key==NULL   ? 0 : key->hashCode()) ^ (value==NULL ? 0 : value->hashCode());
                }

                virtual string toString() {
                    return getKey()->toString() + "=" + getValue()->toString();
                }

                virtual void recordAccess(JHashMap*) {
                }

                virtual void recordRemoval(JHashMap*) {
                }
            };

            JSet* internalEntrySet;
            vector<JEntryImpl*>* table;
            jint isize;
            jint threshold;
            jfloat loadFactor;
            jint modCount;
            void init(jint initialCapacity, jfloat loadFactor);
            void putForCreate(JObject* key, JObject* value);
            JObject *putForNullKey(JObject* value);
            JEntryImpl* removeMapping(JObject* o);
            JEntryImpl* removeEntryForKey(JObject* key);
            jbool containsNullValue();
            void addEntry(jint hash, JObject* key, JObject* value, jint bucketIndex);
            void createEntry(jint hash, JObject* key, JObject* value, jint bucketIndex);
            JSet* entrySet0();
            JEntryImpl* getEntry(JObject* key);
            JIterator* newKeyIterator();
            JIterator* newValueIterator();
            JIterator* newEntryIterator();
            friend class JHashIterator;
            friend class JKeySetImpl;
            friend class JValues;
            friend class JEntrySetImpl;

        public:
            JHashMap(jint initialCapacity = 10, jfloat loadFactor=0.75);
            JHashMap(JHashMap* c);
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
