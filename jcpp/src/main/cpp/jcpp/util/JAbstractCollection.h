#ifndef JABSTRACTCOLLECTION_H
#define JABSTRACTCOLLECTION_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JCollection.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JAbstractCollection: public JObject, public JCollection{
        protected:
            JAbstractCollection(JClass* _class);

        public:
            static JClass* getClazz();
            virtual bool isEmpty();
            virtual bool contains(JObject* o);
            virtual JPrimitiveArray* toArray();
            virtual bool add(JObject* e);
            virtual bool remove(JObject* o);
            virtual bool containsAll(JCollection* c);
            virtual bool addAll(JCollection* c);
            virtual bool removeAll(JCollection* c);
            virtual bool retainAll(JCollection* c);
            virtual void clear();
            virtual string toString();
            virtual ~JAbstractCollection();
        };
    }
}

#endif // JABSTRACTCOLLECTION_H
