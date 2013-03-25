#ifndef JHASHSET_H
#define JHASHSET_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractSet.h"
#include "JCPP.h"
#include "JRandomAccess.h"
#include "JCloneable.h"
#include "JSerializable.h"
#include "JSet.h"
#include "JHashMap.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JHashSet : public JAbstractSet, public JCloneable, public JSerializable{
        protected:
            JHashMap* map;

        public:
            JHashSet(jint initialCapacity = 10, jfloat loadFactor=0);
            JHashSet(JCollection* c);
            static JClass* getClazz();
            virtual JIterator* iterator();
            virtual jint size();
            virtual JPrimitiveArray* toArray();
            virtual jbool containsAll(JCollection* c);
            virtual jbool addAll(JCollection* c);
            virtual jbool removeAll(JCollection* c);
            virtual jbool retainAll(JCollection* c);
            virtual jbool equals(JObject* c);
            virtual jint hashCode();
            virtual bool isEmpty();
            virtual bool contains(JObject* o);
            virtual bool add(JObject* item);
            virtual bool remove(JObject* e);
            virtual void clear();
            virtual JHashSet* clone();
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            virtual ~JHashSet();
        };
    }
}
#endif // JHASHSET_H
