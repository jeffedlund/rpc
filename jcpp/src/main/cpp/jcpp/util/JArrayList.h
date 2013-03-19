#ifndef JARRAYLIST_H
#define JARRAYLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractList.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JArrayList : public JAbstractList{
        protected:
            vector<JObject*>* items;
            JPrimitiveInt* isize;

        public:
            JArrayList(int initialCapacity = 10);
            JArrayList(JCollection* c);
            static JClass* getClazz();
            bool operator==(JObject &other);
            virtual void setPSize(JPrimitiveInt* s);
            virtual JPrimitiveInt* getPSize();
            virtual void trimToSize();
            virtual void ensureCapacity(jint minCapacity);
            virtual jint size();
            virtual bool isEmpty();
            virtual bool contains(JObject* o);
            virtual jint indexOf(JObject* o);
            virtual jint lastIndexOf(JObject* o);
            virtual JArrayList* clone();
            virtual JObject* get(int index);
            virtual JObject* set(jint index, JObject* element);
            virtual bool add(JObject* item);
            virtual void add(int index,JObject* item);
            virtual JObject* remove(int index);
            virtual bool remove(JObject* e);
            virtual void clear();
            virtual bool addAll(JCollection* c);
            virtual bool addAll(jint index, JCollection* c);
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            virtual ~JArrayList();
        };
    }
}

#endif // JARRAYLIST_H
