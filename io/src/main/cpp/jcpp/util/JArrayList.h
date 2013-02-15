#ifndef JARRAYLIST_H
#define JARRAYLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractList.h"
using namespace std;
using namespace jcpp::io;

//TODO implement most of util classes
namespace jcpp{
    namespace util{
        class JArrayList : public JAbstractList{
        protected:
            vector<JObject*>* items;
            JPrimitiveInt* size;

        public:
            JArrayList(int initialCapacity = 10);

            static JClass* getClazz();

            bool operator==(JObject &other);

            jint getSize();

            void setPSize(JPrimitiveInt* s);

            JPrimitiveInt* getPSize();

            bool isEmpty();

            JObject* get(int index);

            void add(JObject* item);

            void add(int index,JObject* item);

            JObject* remove(int index);

            bool remove(JObject* e);

            void clear();

            virtual void writeObject(JObjectOutputStream* out);

            virtual void readObject(JObjectInputStream* in);

            ~JArrayList();
        };
    }
}

#endif // JARRAYLIST_H
