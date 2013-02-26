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
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JAbstractList : public JAbstractCollection, public JList{
        protected:
            JAbstractList(JClass* _class);

        public:

            static JClass* getClazz();
            virtual ~JAbstractList();
        };
    }
}

#endif // JABSTRACTLIST_H
