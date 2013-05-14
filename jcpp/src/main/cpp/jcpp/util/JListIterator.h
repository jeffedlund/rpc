#ifndef JLISTITERATOR_H
#define JLISTITERATOR_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
#include "JIterator.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JListIterator : public JIterator{
        public:
            static JClass* getClazz();
            virtual jbool hasNext()=0;
            virtual JObject* next()=0;
            virtual jbool hasPrevious()=0;
            virtual JObject* previous()=0;
            virtual jint nextIndex()=0;
            virtual jint previousIndex()=0;
            virtual void remove()=0;
            virtual void set(JObject*)=0;
            virtual void add(JObject*)=0;
            virtual ~JListIterator();
        };
    }
}

#endif // JLISTITERATOR_H
