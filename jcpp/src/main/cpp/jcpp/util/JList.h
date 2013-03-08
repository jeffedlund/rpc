#ifndef JLIST_H
#define JLIST_H

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
        class JCPP_LIBRARY_EXPORT JList : public JCollection{

        public:

            static JClass* getClazz();

            virtual ~JList();

        };
    }
}

#endif // JLIST_H
