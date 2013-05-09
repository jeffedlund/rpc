#ifndef JHASHTABLE_H
#define JHASHTABLE_H

#include "JObject.h"
#include <map>
#include "JCPP.h"
#include "JMap.h"
#include "JDictionary.h"
#include "JCloneable.h"
#include "JSerializable.h"
using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JHashtable : public JDictionary, public JMap, public JCloneable, public JSerializable{
            map<JObject*,JObject*,JObject::POINTER_COMPARATOR>* table;
            JPrimitiveInt* threshold;
            JPrimitiveFloat* loadFactor;
            jint modCount;
            void init(jint initialCapacity, jfloat loadFactor);
            JEnumeration* getEnumeration(jint type);
            JIterator* getIterator(jint type);
            friend class JHashtableKeySetImpl;
            friend class JHashtableClass;
            friend class JHashtableEnumeratorImpl;
            friend class JHashtableValues;
            friend class JHashtableEntrySetImpl;


        public:
            JHashtable(jint initialCapacity = 10, jfloat loadFactor=0.75);
            JHashtable(JMap* c);
            static JClass* getClazz();
            virtual jint size();
            virtual bool isEmpty();
            virtual JEnumeration* keys();
            virtual JEnumeration* elements();
            virtual jbool contains(JObject* value);
            virtual jbool containsValue(JObject* value);
            virtual jbool containsKey(JObject* key);
            virtual JObject* get(JObject* key);
            virtual JObject* put(JObject* key, JObject* value);
            virtual JObject* remove(JObject* key);
            virtual void putAll(JMap* m);
            virtual void clear();
            virtual JHashtable* clone();
            virtual JString toString();
            virtual JSet* keySet();
            virtual JSet* entrySet();
            virtual JCollection* values();
            virtual jbool equals(JObject*);
            virtual jint hashCode();
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            virtual ~JHashtable();
        };
    }
}

#endif // JHASHTABLE_H
