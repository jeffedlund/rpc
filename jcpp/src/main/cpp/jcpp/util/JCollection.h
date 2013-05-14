#ifndef JCOLLECTION_H
#define JCOLLECTION_H

#include "JInterface.h"
#include "JIterable.h"
#include "JPrimitiveArray.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JCollection : public JIterable{
        public:
            static JClass* getClazz();
            virtual jint size()=0;
            virtual jbool isEmpty()=0;
            virtual jbool contains(JObject*)=0;
            virtual JIterator* iterator()=0;
            virtual JPrimitiveArray* toArray()=0;
            virtual jbool add(JObject* e)=0;
            virtual jbool remove(JObject* o)=0;
            virtual jbool containsAll(JCollection* c)=0;
            virtual jbool addAll(JCollection* c)=0;
            virtual jbool removeAll(JCollection* c)=0;
            virtual jbool retainAll(JCollection* c)=0;
            virtual void clear()=0;
            virtual ~JCollection();
        };
    }
}

#endif // JCOLLECTION_H
