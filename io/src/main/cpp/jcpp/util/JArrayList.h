#ifndef JARRAYLIST_H
#define JARRAYLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JSerializable.h"
#include <QtGlobal>
using namespace std;

namespace jcpp{
    namespace util{
        //TODO implement most of util classes ...
        class JArrayList : public JObject, public JCollection//public JSerializable,
        {
            vector<JObject*>* items;

         //   void writeObject(MObjectOutputStream *s);

         //   void readObject(MObjectInputStream *s);

        public:
            JArrayList(int initialCapacity = 10);

            static JClass* getClazz();

            qint32 getSize();

            bool isEmpty();

            JObject* get(int index);

            void add(JObject* item);

            void clear();

            ~JArrayList();
        };
    }
}

#endif // JARRAYLIST_H
