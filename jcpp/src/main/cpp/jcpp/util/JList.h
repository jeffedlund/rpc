#ifndef JLIST_H
#define JLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JCollection.h"
#include "JIterator.h"
#include "JListIterator.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JList : public JCollection{

        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual bool isEmpty()=0;
            virtual bool contains(JObject* o)=0;
            virtual JIterator* iterator()=0;
            //TODO Object[] toArray();
            //TODO <T> T[] toArray(T[] a);
            virtual bool add(JObject* e)=0;
            virtual bool remove(JObject* o)=0;
            virtual bool containsAll(JCollection* c)=0;
            virtual bool addAll(JCollection* c)=0;
            virtual bool addAll(jint index, JCollection* c)=0;
            virtual bool removeAll(JCollection* c)=0;
            virtual bool retainAll(JCollection* c)=0;
            virtual void clear()=0;
            virtual bool equals(JObject* o)=0;
            virtual jint hashCode()=0;
            virtual JObject* get(jint index)=0;
            virtual JObject* set(jint index, JObject* element)=0;
            virtual void add(jint index, JObject* element)=0;
            virtual JObject* remove(jint index)=0;
            virtual jint indexOf(JObject* o)=0;
            virtual jint lastIndexOf(JObject* o)=0;
            virtual JListIterator* listIterator()=0;
            virtual JListIterator* listIterator(jint index)=0;
            virtual JList* subList(jint fromIndex, jint toIndex)=0;
            virtual ~JList();

        };
    }
}

#endif // JLIST_H
