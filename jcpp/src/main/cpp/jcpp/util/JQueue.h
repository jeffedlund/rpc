#ifndef JQUEUE_H
#define JQUEUE_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JCollection.h"
#include "JIterator.h"
#include "JListIterator.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JQueue : public JCollection{
        public:
            static JClass* getClazz();
            virtual jbool add(JObject* e)=0;
            virtual jbool offer(JObject* e)=0;
            virtual JObject* remove()=0;
            virtual JObject* poll()=0;
            virtual JObject* element()=0;
            virtual JObject* peek()=0;
            virtual ~JQueue();
        };
    }
}


#endif // JQUEUE_H
