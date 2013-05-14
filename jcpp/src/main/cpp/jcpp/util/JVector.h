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
            virtual void setElementCount(JPrimitiveInt* s);
            virtual JPrimitiveInt* getElementCount();
            virtual void setCapacityIncrement(JPrimitiveInt* s);
            virtual JPrimitiveInt* getCapacityIncrement();
            jint getModCount();
            friend class JVectorClass;
            friend class JVectorItr;
            friend class JVectorListItr;

        public:
            JVector(jint initialCapacity = 10, jint capacityIncrement=0);
            JVector(JCollection* c);
            static JClass* getClazz();
            void copyInto(JPrimitiveArray* anArray);
            void trimToSize();
            void ensureCapacity(jint minCapacity);
            void setSize(jint newSize);
            jint capacity();
            virtual jint size();
            virtual jbool isEmpty();
            virtual JIterator* iterator();
            virtual JListIterator* listIterator();
            virtual JListIterator* listIterator(jint index);
            virtual JEnumeration* elements();
            virtual jbool contains(JObject* o);
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
            virtual JPrimitiveArray* toArray();
            virtual JVector* clone();
            virtual JObject* get(jint index);
            virtual JObject* set(jint index, JObject* element);
            virtual jbool add(JObject* item);
            virtual jbool remove(JObject* e);
            virtual void add(jint index,JObject* item);
            virtual JObject* remove(jint index);
            virtual void clear();
            virtual jbool containsAll(JCollection* c);
            virtual jbool addAll(JCollection* c);
            virtual jbool removeAll(JCollection* c);
            virtual jbool retainAll(JCollection* c);
            virtual jbool addAll(jint index, JCollection* c);
            virtual jbool equals(JObject* other);
            virtual jint hashCode();
            virtual JString toString();
            virtual JList* subList(jint fromIndex, jint toIndex);
            virtual void removeRange(jint fromIndex, jint toIndex);
            virtual void writeObject(JObjectOutputStream* out);
            virtual ~JVector();
        };
    }
}

#endif // JVECTOR_H
