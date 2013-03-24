#ifndef JABSTRACTSET_H
#define JABSTRACTSET_H

#include "JObject.h"
#include "JCollection.h"
#include "JExternalizable.h"
#include "Object.h"
#include "JObjectInputStream.h"
#include "JObjectOutputStream.h"
#include "JAbstractCollection.h"
#include "JSet.h"
#include "JListIterator.h"
#include "JCPP.h"
using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JAbstractSet : public JAbstractCollection, public JSet{
        protected:
            JAbstractSet(JClass* _class);

        public:
            static JClass* getClazz();
            virtual JPrimitiveArray* toArray();
            virtual jint size()=0;
            virtual jbool isEmpty();
            virtual JIterator* iterator()=0;
            virtual jbool add(JObject* e);
            virtual jbool remove(JObject* o);
            virtual jbool containsAll(JCollection* c);
            virtual jbool addAll(JCollection* c);
            virtual jbool retainAll(JCollection* c);
            virtual jbool removeAll(JCollection* c);
            virtual jbool equals(JObject* o);
            virtual jint hashCode();
            virtual ~JAbstractSet();
        };
    }
}


#endif // JABSTRACTSET_H
