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
            friend class JItr;
            friend class JListIteratorImpl;
            friend class JListItr;
            friend class JSubList;
            friend class JArrayListItr;
            friend class JArrayListListItr;
            friend class JArrayListSubList;
            friend class JArrayListSubListIterator;

        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual jbool isEmpty();
            virtual jbool add(JObject* e);
            virtual JObject* set(jint index, JObject* element);
            virtual void add(jint index, JObject* element);
            virtual jbool remove(JObject* o);
            virtual JObject* remove(jint jindex);
            virtual jbool contains(JObject* o);
            virtual jbool containsAll(JCollection* c);
            virtual jbool removeAll(JCollection* c);
            virtual jbool retainAll(JCollection* c);
            virtual jint indexOf(JObject* o);
            virtual jint lastIndexOf(JObject* o);
            virtual void clear();
            virtual jbool addAll(jint index, JCollection* c);
            virtual JPrimitiveArray* toArray();
            virtual JIterator* iterator();
            virtual JListIterator* listIterator();
            virtual JListIterator* listIterator(jint index);
            virtual JList* subList(jint fromIndex, jint toIndex);
            virtual jbool equals(JObject* o);
            virtual jint hashCode();
            virtual void removeRange(jint fromIndex, jint toIndex);
            virtual ~JAbstractList();
        };
    }
}

#endif // JABSTRACTLIST_H
