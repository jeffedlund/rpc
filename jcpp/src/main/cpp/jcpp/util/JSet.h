#ifndef JSET_H
#define JSET_H

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
        class JCPP_LIBRARY_EXPORT JSet : public JCollection{

        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual jbool isEmpty()=0;
            virtual jbool contains(JObject* o)=0;
            virtual JIterator* iterator()=0;
            virtual JPrimitiveArray* toArray()=0;
            virtual jbool add(JObject* e)=0;
            virtual jbool remove(JObject* o)=0;
            virtual jbool containsAll(JCollection* c)=0;
            virtual jbool addAll(JCollection* c)=0;
            virtual jbool retainAll(JCollection* c)=0;
            virtual jbool removeAll(JCollection* c)=0;
            virtual void clear()=0;
            virtual jbool equals(JObject* o)=0;
            virtual jint hashCode()=0;
            virtual ~JSet();
        };
    }
}
#endif // JSET_H
