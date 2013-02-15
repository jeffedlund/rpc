#ifndef JLIST_H
#define JLIST_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JCollection.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JList : public JCollection{

        public:

            static JClass* getClazz();

        };
    }
}

#endif // JLIST_H
