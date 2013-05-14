#ifndef JABSTRACTQUEUE_H
#define JABSTRACTQUEUE_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractCollection.h"
#include "JQueue.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JAbstractQueue : public JAbstractCollection, public JQueue{
        protected:
            JAbstractQueue(JClass* _class);

        public:
            static JClass* getClazz();
            virtual jbool add(JObject* e);
            virtual JObject* remove();
            virtual JObject* element();
            virtual void clear();
            virtual jbool addAll(JCollection* c);
            virtual ~JAbstractQueue();
        };
    }
}

#endif // JABSTRACTQUEUE_H
