#ifndef JVECTOR_H
#define JVECTOR_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractList.h"
#include "JCPP.h"
#include "JRandomAccess.h"
#include "JCloneable.h"
#include "JEnumeration.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JVector : public JAbstractList, public JRandomAccess, public JSerializable, public JCloneable{
        protected:
            vector<JObject*>* items;
            JPrimitiveInt* elementCount;
            JPrimitiveInt* capacityIncrement;

        public:
            JVector(jint initialCapacity = 10, jint capacityIncrement=0);
            JVector(JCollection* c);
            static JClass* getClazz();
            virtual void setElementCount(JPrimitiveInt* s);
            virtual JPrimitiveInt* getElementCount();
            virtual void setCapacityIncrement(JPrimitiveInt* s);
            virtual JPrimitiveInt* getCapacityIncrement();
            void copyInto(JPrimitiveArray* anArray);
            void trimToSize();
            void ensureCapacity(jint minCapacity);
            void setSize(int newSize);
            jint capacity();
            virtual jint size();
            virtual bool isEmpty();
            virtual JIterator* iterator();
            virtual JListIterator* listIterator();
            virtual JListIterator* listIterator(jint index);
            virtual JEnumeration* elements();
            virtual bool contains(JObject* o);
            virtual jint indexOf(JObject* o);
            virtual jint indexOf(JObject* o,jint index);
            virtual jint lastIndexOf(JObject* o);
            virtual jint lastIndexOf(JObject* o,jint index);
            virtual JObject* elementAt(jint index);
            virtual JObject* firstElement();
            virtual JObject* lastElement();
            virtual void setElementAt(JObject* obj, jint index);
            virtual void removeElementAt(jint index);
            virtual void insertElementAt(JObject* obj, jint index);
            virtual void addElement(JObject* obj);
            virtual bool removeElement(JObject* obj);
            virtual void removeAllElements();
            virtual JVector* clone();
            virtual JObject* get(int index);
            virtual JObject* set(jint index, JObject* element);
            virtual bool add(JObject* item);
            virtual bool remove(JObject* e);
            virtual void add(int index,JObject* item);
            virtual JObject* remove(int index);
            virtual void clear();
            virtual bool containsAll(JCollection* c);
            virtual bool addAll(JCollection* c);
            virtual bool removeAll(JCollection* c);
            virtual bool retainAll(JCollection* c);
            virtual bool addAll(jint index, JCollection* c);
            virtual bool equals(JObject* other);
            virtual jint hashCode();
            virtual string toString();
            virtual JList* subList(jint fromIndex, jint toIndex);
            virtual void removeRange(jint fromIndex, jint toIndex);
            virtual void writeObject(JObjectOutputStream* out);
            virtual ~JVector();
        };
    }
}

#endif // JVECTOR_H
