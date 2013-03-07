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
            virtual ~JAbstractCollection();
        };
    }
}

#endif // JABSTRACTCOLLECTION_H
