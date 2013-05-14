#ifndef JITERATOR_H
#define JITERATOR_H

#include "JObject.h"
#include "JInterface.h"
#include "JCPP.h"
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_LIBRARY_EXPORT JIterator : public JInterface{
        public:
            static JClass* getClazz();
            virtual jbool hasNext()=0;
            virtual JObject* next()=0;
            virtual void remove()=0;
            virtual ~JIterator();
        };
    }
}

#endif // JITERATOR_H
