#ifndef JABSTRACTLIST_H
#define JABSTRACTLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractCollection.h"
#include "JList.h"
#include "JListIterator.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JAbstractList : public JAbstractCollection, public JList{
        protected:
            jint modCount;
            JAbstractList(JClass* _class);

        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual bool isEmpty();
            virtual bool add(JObject* e);
            virtual JObject* set(jint index, JObject* element);
            virtual void add(jint index, JObject* element);
            virtual bool remove(JObject* o);
            virtual JObject* remove(jint jindex);
            virtual bool contains(JObject* o);
            virtual bool containsAll(JCollection* c);
            virtual bool removeAll(JCollection* c);
            virtual bool retainAll(JCollection* c);
            virtual jint indexOf(JObject* o);
            virtual jint lastIndexOf(JObject* o);
            virtual void clear();
            virtual bool addAll(jint index, JCollection* c);
            virtual JPrimitiveArray* toArray();
            virtual JIterator* iterator();
            virtual JListIterator* listIterator();
            virtual JListIterator* listIterator(jint index);
            virtual JList* subList(jint fromIndex, jint toIndex);
            virtual bool equals(JObject* o);
            virtual jint hashCode();
            virtual void removeRange(jint fromIndex, jint toIndex);
            virtual jint getModCount();
            virtual void incrementModCount();
            virtual ~JAbstractList();
        };
    }
}

#endif // JABSTRACTLIST_H
