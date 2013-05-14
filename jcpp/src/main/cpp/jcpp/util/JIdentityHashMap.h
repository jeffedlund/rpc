#ifndef JIDENTITYHASHMAP_H
#define JIDENTITYHASHMAP_H

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
        class JCPP_LIBRARY_EXPORT JIdentityHashMap : public JAbstractMap, public JCloneable, public JSerializable{
        protected:
            map<JObject*, JObject*, JObject::POINTER_ID_COMPARATOR>* table;
            jint modCount;
            JPrimitiveInt* isize;
            void init();
            friend class JIdentityHashMapClass;
            friend class JIdentityHashMapIterator;

        public:
            JIdentityHashMap(jint initialCapacity = 10);
            JIdentityHashMap(JMap* c);
            static JClass* getClazz();
            virtual jint size();
            virtual jbool isEmpty();
            virtual JObject* get(JObject* key);
            virtual jbool containsKey(JObject* key);
            virtual jbool containsValue(JObject* value);
            virtual JObject* put(JObject* key, JObject* value);
            virtual void putAll(JMap* m);
            virtual JObject* remove(JObject* key);
            virtual void clear();
            /*TODO virtual jbool equals(JObject* o);
            virtual jint hashCode();*/
            virtual JIdentityHashMap* clone();
            virtual JSet* keySet();
            virtual JCollection* values();
            virtual JSet* entrySet();
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            virtual ~JIdentityHashMap();
        };
    }
}
#endif // JIDENTITYHASHMAP_H
